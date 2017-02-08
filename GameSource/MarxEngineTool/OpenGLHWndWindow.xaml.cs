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
using LogicCommon;
using System.Xml;
using System.IO;
using AvalonDock.MVVMTestApp;
using Xceed.Wpf.AvalonDock.Layout.Serialization;

namespace MarxEngineTool
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class OpenGLHWndWindow 
    {
        public OpenGLHWndWindow()
        {
            InitializeComponent();
            before = new DateTime();

        }

        //private HwndHost host;
        private int fps;
        private DateTime before;
        public static WPFOpenGLLib.OpenGLHwnd OpenGl2Md2;

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
            Workspace.This.OpenGl2Md2 = OpenGl2Md2;
            OpenGl2Md2.SetModerObj(hwndPlaceholder);

            var serializer = new Xceed.Wpf.AvalonDock.Layout.Serialization.XmlLayoutSerializer(dockManager);
            serializer.LayoutSerializationCallback += (s, args) =>
            {
                args.Content = args.Content;
            };
#if DEBUG

//#else
            if (File.Exists(@".\AvalonDock.config"))
                serializer.Deserialize(@".\AvalonDock.config");
#endif
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

        private void MetroWindow_Unloaded(object sender, RoutedEventArgs e)
        {
#if DEBUG

#else
            var serializer = new Xceed.Wpf.AvalonDock.Layout.Serialization.XmlLayoutSerializer(dockManager);
            serializer.Serialize(@".\AvalonDock.config");
#endif
        }



        #region LoadLayoutCommand
        RelayCommand _loadLayoutCommand = null;
        public ICommand LoadLayoutCommand
        {
            get
            {
                if (_loadLayoutCommand == null)
                {
                    _loadLayoutCommand = new RelayCommand((p) => OnLoadLayout(p), (p) => CanLoadLayout(p));
                }

                return _loadLayoutCommand;
            }
        }

        private bool CanLoadLayout(object parameter)
        {
            return File.Exists(@".\AvalonDock.Layout.config");
        }

        private void OnLoadLayout(object parameter)
        {
            var layoutSerializer = new XmlLayoutSerializer(dockManager);
            //Here I've implemented the LayoutSerializationCallback just to show
            // a way to feed layout desarialization with content loaded at runtime
            //Actually I could in this case let AvalonDock to attach the contents
            //from current layout using the content ids
            //LayoutSerializationCallback should anyway be handled to attach contents
            //not currently loaded
            layoutSerializer.LayoutSerializationCallback += (s, e) =>
            {
                //if (e.Model.ContentId == FileStatsViewModel.ToolContentId)
                //    e.Content = Workspace.This.FileStats;
                //else if (!string.IsNullOrWhiteSpace(e.Model.ContentId) &&
                //    File.Exists(e.Model.ContentId))
                //    e.Content = Workspace.This.Open(e.Model.ContentId);
            };
            layoutSerializer.Deserialize(@".\AvalonDock.Layout.config");
        }

#endregion

#region SaveLayoutCommand
        RelayCommand _saveLayoutCommand = null;
        public ICommand SaveLayoutCommand
        {
            get
            {
                if (_saveLayoutCommand == null)
                {
                    _saveLayoutCommand = new RelayCommand((p) => OnSaveLayout(p), (p) => CanSaveLayout(p));
                }

                return _saveLayoutCommand;
            }
        }

        private bool CanSaveLayout(object parameter)
        {
            return true;
        }

        private void OnSaveLayout(object parameter)
        {
            var layoutSerializer = new XmlLayoutSerializer(dockManager);
            layoutSerializer.Serialize(@".\AvalonDock.Layout.config");
        }

#endregion
    }
}
