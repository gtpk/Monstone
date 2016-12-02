using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WPFOpenGLApp
{
    /// <summary>
    /// Interaction logic for UserControlWindow.xaml
    /// </summary>
    public partial class OpenGLUserControlWindow : Window
    {
        private System.Windows.Threading.DispatcherTimer updateTimer = new System.Windows.Threading.DispatcherTimer();	//Refresh  timer

        public OpenGLUserControlWindow()
        {
            InitializeComponent();
        }

        public override void BeginInit()
        {
            updateTimer.Interval = new TimeSpan(160000);
            updateTimer.Tick += new EventHandler(updateTimer_Tick);
            updateTimer.Start();
            base.BeginInit();
        }

        protected override void OnClosing(System.ComponentModel.CancelEventArgs e)
        {
            base.OnClosing(e);

            if (!e.Cancel)
            {
                if (null != updateTimer)
                {
                    updateTimer.Stop();
                    updateTimer = null;
                }
            }
        }

        private void updateTimer_Tick(object sender, EventArgs e)
        {
            windowsFormsHost1.Child.Invalidate();
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape)
            {
                
                this.Close();
            }
        }
    }
}
