using System;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;
using App4.Core;

namespace App4.Views
{
	[XamlCompilation(XamlCompilationOptions.Compile)]
	public partial class AboutPage : ContentPage
	{
		public AboutPage ()
		{
			InitializeComponent ();
		}

        private async void btnTest_Clicked(object sender, EventArgs e)
        {
           var res = await Core.Core.IsAvailable(entryIP.Text);
            if (res)
            {
                btnTest.BackgroundColor = Color.Green;
                SetBtnEnable();
                ReadSettings();
            }
            else
            {
                btnTest.BackgroundColor = Color.Red;
                SetBtnDisable();
            }
               
        }

        private async void ReadSettings()
        {
            string url = "http://"+entryIP.Text+"/st";
            var response = await Core.Core.GetRespone(url);          
            try
            {
                Console.Out.WriteLine(" response => {0}", response);
                var res = response.Split('|');
                Console.Out.WriteLine(" res => {0}", res.Length);
                if (res.Length == 5)
                {
                    entryMode.Text = PrevedNaMode(res[0]);
                    entryCasV.Text = PrevedNaCas(res[1]);
                    entryCasH.Text = PrevedNaCas(res[2]);
                    entryPin1.Text = res[3];
                    entryPin2.Text = res[4];
                }
            }
            catch
            {
                Console.Out.WriteLine("invalit response => {0}", response);
            }
          //  url = "http://" + entryIP.Text + "/p1";
          //  response = await Core.Core.GetRespone(url);
          //  entryPin1.Text = response;
          //  url = "http://" + entryIP.Text + "/p2";
           // response = await Core.Core.GetRespone(url);
           // entryPin2.Text = response;
        }

        private string PrevedNaMode(string v)
        {
            
            int mode = int.Parse(v);
            switch (mode)
            {
                case 1: return "mode 1";
                case 2: return "mode 2";
                case 3: return "mode 2";
            }
            return "neco";
        }

        private string PrevedNaCas(string v)
        {
            long cas = long.Parse(v);
            int h;
            int m;
            int s;
            h = (int)(cas / 3600);
            m = (int)(cas - h * 3600) / 60;
            s = (int)(cas- (m * 60 + h * 3600));
            return string.Format("{0}:{1}:{2}", h, m, s);
        }

        private void SetBtnDisable()
        {
            btnEnableMode.IsEnabled = false;
            btnEnableCasV.IsEnabled = false;
            btnEnableCasH.IsEnabled = false;
            btnEnablePin1.IsEnabled = false;
            btnEnablePin2.IsEnabled = false;
        }

        private void SetBtnEnable()
        {
            btnEnableMode.IsEnabled = true;
            btnEnableCasV.IsEnabled = true;
            btnEnableCasH.IsEnabled = true;
            btnEnablePin1.IsEnabled = true;
            btnEnablePin2.IsEnabled = true;
        }

        private void btnEnableMode_Clicked(object sender, EventArgs e)
        {
            var btn = (Button)sender;
            var n = btn.Id;
            if(btn.Text == "edit")
            {
                btn.Text = "Finish";
                EnableEdit(btn);
            }
            else
            {
                btn.Text = "edit";
                DisableEdit(btn);
                //Send();
            }                                     
        }

        private void DisableEdit(Button btn)
        {
            if (btn == btnEnableMode)
                entryMode.IsEnabled = false;
            else
                if (btn == btnEnableCasH)
                    entryCasH.IsEnabled = false;
                else
                    if (btn == btnEnableCasV)
                        entryCasV.IsEnabled = false;
                    else
                        if (btn == btnEnablePin1)
                            entryPin1.IsEnabled = false;
                        else
                            if (btn == btnEnablePin2)
                                entryPin2.IsEnabled = false;
        }

        private void EnableEdit(Button btn)
        {
            if (btn == btnEnableMode)
                entryMode.IsEnabled = true;
            else
                if (btn == btnEnableCasH)
                     entryCasH.IsEnabled = true;
                else
                    if (btn == btnEnableCasV)
                        entryCasV.IsEnabled = true;
                    else
                        if (btn == btnEnablePin1)
                            entryPin1.IsEnabled = true;
                        else
                            if (btn == btnEnablePin2)
                                entryPin2.IsEnabled = true;


        }

        private void Send()
        {
           
        }

       
    }
}