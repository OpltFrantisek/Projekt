using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading.Tasks;

namespace App4.Core
{
    public static  class Core
    {
        public static string ip = "192.168.4.1";
        public async static Task<bool> IsAvailable(string ip_address)
        {
            var ip = ip_address.Split('.').Select(x => byte.Parse(x)).ToArray();
            if (ip.Length != 4)
            {
                Console.Out.WriteLine("Wrong ip address format");
                return false;
            }
            var ping = new Ping();
            var reply = await Task.Run(() =>
            {
                var res = ping.Send(new IPAddress(ip), 1000);
                return res.Status == IPStatus.Success ? true : false;
            });
            return reply;
        }
        public  static string GetRequest(string url)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(url);
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();
            var reader = new StreamReader(response.GetResponseStream());
            var result = reader.ReadLine();
            reader.Dispose();
            response.Dispose();

            return result;
        }
        public static  async Task<string> GetRespone(string url)
        {
            string result = "neco";
            var request = (HttpWebRequest)HttpWebRequest.Create(new Uri(url));
            request.ContentType = "text/plain";
            request.Method = "GET";
            Console.Out.WriteLine(" response => {0}", url);
            using (WebResponse response = await request.GetResponseAsync())
            {
                using (Stream stream = response.GetResponseStream())
                {
                    using (StreamReader sr = new StreamReader(stream))
                    {
                        try
                        {
                            result = sr.ReadLine();
                            Console.Out.WriteLine("result => {0}", result);
                        }
                        catch
                        {
                            result = "neco";
                            Console.Out.WriteLine("result => invalid response : {0} ", sr.ReadLine());
                        }
                    }
                }
            }
            return result;
        }
        public static string PrevedNaMode(string v)
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

        public static string PrevedNaCas(string v)
        {
            string hours, minutes, seconds;
            int h, m, s;
            long cas = long.Parse(v);
;

            h = (int)(cas / 3600);
            m = (int)(cas - h * 3600) / 60;
            s = (int)(cas - (m * 60 + h * 3600));

            if (h < 10)
                hours = "0" + h;
            else
                hours = "" + h;

            if (m < 10)
                minutes = "0" + m;
            else
                minutes = "" + m;

            if (s < 10)
                seconds = "0" + s;
            else
                seconds = "" + s;

            return string.Format("{0}:{1}:{2}", hours, minutes, seconds);
        }
    }
}
