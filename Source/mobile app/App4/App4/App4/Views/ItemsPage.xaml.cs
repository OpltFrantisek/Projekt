using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

using App4.Views;
using System.Threading;

namespace App4.Views
{
	[XamlCompilation(XamlCompilationOptions.Compile)]
	public partial class ItemsPage : ContentPage
	{
        class TimerExampleState
        {
            public int counter = 0;
            public Timer tmr;
        }
        public ItemsPage()
        {
            InitializeComponent();
            TimerExampleState s = new TimerExampleState();
            TimerCallback timerDelegate = new TimerCallback(CheckTime);
            Timer timer = new Timer(timerDelegate, s, 1000, 2000);
            s.tmr = timer;
            labelCas.IsVisible = false;

        }
        private async void btnRestart_Clicked(object sender, EventArgs e)
        {
            string url = "http://" + Core.Core.ip + "/restart";
            var response = await Core.Core.GetRespone(url);           
        }

        private async void CheckTime(object state)
        {
    
        }

        private async  void btnAktivace_Clicked(object sender, EventArgs e)
        {
            var btn = (Button)sender;
            if(btn == btnAktivace)
            {
                string url = "http://" + Core.Core.ip + "/act";
                var response = await Core.Core.GetRespone(url);
                try
                {
                    int res = int.Parse(response);
                    if (res  == 6)
                        btnOK.IsVisible = true;
                }
                catch
                {
                    Console.Out.WriteLine("invalit response => {0}", response);
                }

            }
            else
            {
                string url = "http://" + Core.Core.ip + "/ok";
                var response = await Core.Core.GetRespone(url);
                try
                {
                    int res = int.Parse(response);
                    if (res == 9)
                    {
                        btnOK.IsVisible = false;
                        btnAktivace.BackgroundColor = Color.Green;
                    }
                    else
                    {
                        btnAktivace.BackgroundColor = Color.Red;
                    }
                       
                }
                catch
                {
                    Console.Out.WriteLine("invalit response => {0}", response);
                }

            }
            
        }
    }
}