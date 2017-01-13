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
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Windows.Interop;
using System.Timers;
using LogicTool.ViewModel; //HwndHost

namespace MarxEngineTool
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class OpenGLHWndWindow : Window
    {
        public OpenGLHWndWindow()
        {
            InitializeComponent();
            before = new DateTime();

           
        }

        //private HwndHost host;
        private int fps;
        private DateTime before;
        private WPFOpenGLLib.OpenGLHwnd OpenGl2Md2;

        private System.Windows.Threading.DispatcherTimer updateTimer = new System.Windows.Threading.DispatcherTimer();
  
        public override void BeginInit()
        {
            updateTimer.Interval = new TimeSpan(160);
            //updateTimer.Interval = new TimeSpan(0,0,0,0,160);
            updateTimer.Tick += new EventHandler(updateTimer_Tick);
            //updateTimer.Start();

            base.BeginInit();
        }



        protected override void OnClosing(System.ComponentModel.CancelEventArgs e)
        {
            MessageBoxResult result = MessageBox.Show("저장후 종료 하시겠습니까? \n아니오를 선택할경우 모든 데이터가 삭제 됩니다!", "저장", MessageBoxButton.YesNoCancel);
            if (result == MessageBoxResult.Yes)
            {
                

                if (!e.Cancel)
                {
                    if (null != updateTimer)
                    {
                        updateTimer.Stop();
                        updateTimer = null;
                        OpenGl2Md2.Save();
                    }
                }

                base.OnClosing(e);
            }
            else if (result == MessageBoxResult.No)
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
            else if (result == MessageBoxResult.Cancel)
            {
                e.Cancel = true;
                //base.OnClosing(e);
            }
        }

        private void updateTimer_Tick(object sender, EventArgs e)
        {
            if (null != hwndPlaceholder &&
                null != hwndPlaceholder.Child)
            {
                if (DateTime.Now.Second - before.Second > 1)
                {
                    before = DateTime.Now;
                    //tb_FPS.Text = (fps).ToString();
                    fps = 0;
                }
                else
                {
                    fps++;
                }
                OpenGl2Md2.DrawingCall();
                //hwndPlaceholder.Child.InvalidateVisual();
                
                
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            // Create our OpenGL Hwnd 'control'...
            HwndHost host = new WPFOpenGLLib.OpenGLHwnd();
            OpenGl2Md2 = (WPFOpenGLLib.OpenGLHwnd)host;
 
            // ... and attach it to the placeholder control:
            hwndPlaceholder.Child = host;
            PieceListViewModel.Instance.OpenGl2Md2 = this.OpenGl2Md2;
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape)
            {
                e.Handled = true;
                this.Close();
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            OpenGl2Md2.SetNewPiece("ground_001.md2", "wall_001(2).tga");
        }

        private void MenuItem_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            OpenGl2Md2.Load();
        }

        private void Button_Click_3(object sender, System.Windows.RoutedEventArgs e)
        {
            OpenGl2Md2.SetNewPiece(5,5, "wall_001(2).tga");
        }

        private void Button_Click(object sender, System.Windows.RoutedEventArgs e)
        {
        	OpenGl2Md2.SetNewPiece(5,5, "wall_001(2).tga");
        }

        private void Button_Click_4(object sender, RoutedEventArgs e)
        {

            OpenGl2Md2.Load();
        }
    }
}
