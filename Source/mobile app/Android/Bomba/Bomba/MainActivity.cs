using Android.App;
using Android.OS;
using Android.Widget;
using System;
using System.IO;
using System.Net;
using System.Net.NetworkInformation;
using System.Threading.Tasks;
using System.Linq;

namespace Bomba
{
    [Activity(Label = "Bomba", MainLauncher = true)]
    public class MainActivity : Activity
    {
        Button buttonActivation;
        Button buttonOK;
        Button buttonTest;
        Button buttonLock;
        Button buttonLockOk;
        EditText editTextIP;
        protected override void OnCreate(Bundle savedInstanceState)
        {
            base.OnCreate(savedInstanceState);

            // Set our view from the "main" layout resource
            SetContentView(Resource.Layout.UI);

            // tady bude neco
            buttonActivation = FindViewById<Button>(Resource.Id.buttonActivation);
            buttonOK = FindViewById<Button>(Resource.Id.buttonOk);
            buttonTest = FindViewById<Button>(Resource.Id.buttonTest);
            buttonLock = FindViewById<Button>(Resource.Id.buttonLock);
            buttonLockOk = FindViewById<Button>(Resource.Id.buttonLockOk);
            editTextIP = FindViewById<EditText>(Resource.Id.editTextIp);

            buttonOK.Visibility = Android.Views.ViewStates.Invisible;
            buttonLockOk.Visibility = Android.Views.ViewStates.Invisible;

            buttonOK.Enabled = false;
            buttonLockOk.Enabled = false;

            editTextIP.Enabled = false;

            buttonOK.Click += Click_Event;
            buttonActivation.Click += Click_Event;

            buttonLock.Click += ButtonLock_Click;
            buttonLockOk.Click += ButtonLock_Click;

            buttonTest.Click += ButtonTest_Click;


        }

        async void ButtonTest_Click(object sender, EventArgs e)
        {
            var ip = editTextIP.Text.Split('.').Select(x => byte.Parse(x)).ToArray();
            if(ip.Length != 4)
            {
                Console.Out.WriteLine("Wrong ip address format");
                return;
            }

            var ping = new Ping();
            var reply = await Task.Run(() =>
            {
               var res =  ping.Send(new IPAddress(ip), 1000);
                return res.Status == IPStatus.Success ? true : false;
            });

            if (reply)          
                buttonTest.Background =  GetDrawable(Android.Resource.Color.HoloGreenDark);
            else
                buttonTest.Background = GetDrawable(Android.Resource.Color.HoloRedDark);


        }

        private void ButtonLock_Click(object sender, EventArgs e)
        {
            var neco = sender as Button;
            var buttonAct = neco.Id == buttonLock.Id ? true : false;

            if(!buttonLockOk.Enabled && buttonAct)
            {
                buttonLock.Enabled = false;
                buttonLockOk.Enabled = true;
                buttonLockOk.Visibility = Android.Views.ViewStates.Visible;           
            }
            else
            {
                buttonLock.Enabled = true;
                buttonLockOk.Enabled = false;
                buttonLockOk.Visibility = Android.Views.ViewStates.Invisible;

                editTextIP.Enabled = !editTextIP.Enabled;

            }
        }

         void Click_Event(object sender, EventArgs e)
        {
            var neco = sender as Button;
            var buttonAct = neco.Id == buttonActivation.Id ? true : false;
                
            string url = "http://"+GetString(Resource.String.default_ip) + (buttonAct? "/act": "/ok");
            Console.Out.WriteLine("url => {0}", url);
           // var result = GetRequest(u);
            //StreamReader reader = new StreamReader(GetRequest(url));
            //string s = reader.ReadToEnd();
            string s = GetRequest(url);
            int result;
            try
             {
                result = int.Parse(s);
                Console.Out.WriteLine("result => {0}", result);
            }
            catch
            {
                result = 0;
                Console.Out.WriteLine("result => invalid response : {0} ", s);
            }
            if (result == 6 && buttonAct)
            {
                buttonOK.Visibility = Android.Views.ViewStates.Visible;
                buttonOK.Enabled = true;
            }
            else
            {
                if(result == 9 && !buttonAct)
                {
                    buttonOK.Visibility = Android.Views.ViewStates.Invisible;
                    buttonOK.Enabled = false;
                    buttonActivation.Text = GetString(Resource.String.activation_success);        
                }
                else
                    Console.Out.WriteLine("Wrong result");
            }
            
            
        }
        private static string GetRequest(string url)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            var reader = new StreamReader(response.GetResponseStream());
            var result = reader.ReadLine();
            reader.Dispose();
            response.Dispose();
           
            return  result;
        }

        private async Task<int> GetRespone(string url)
        {
            var result = 0;
            var request = (HttpWebRequest)HttpWebRequest.Create(new Uri(url));
            request.ContentType = "text/plain";
            request.Method = "GET";
            using(WebResponse response = await  request.GetResponseAsync())
            {
                using (Stream stream = response.GetResponseStream())
                {
                    using(StreamReader sr = new StreamReader(stream))
                    {
                        try
                        {
                            result = int.Parse(sr.ReadLine());
                            Console.Out.WriteLine("result => {0}", result);
                        }
                        catch
                        {
                            result = 0;
                            Console.Out.WriteLine("result => invalid response : {0} ",sr.ReadLine());
                        }
                    }
                }
            }
            return result;
        }
    }

}

