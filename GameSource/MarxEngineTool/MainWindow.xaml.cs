using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using LogicTool;

namespace MarxEngineTool
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {

        // Keep track of all the windows we opened so far
        private List<OpenGLUserControlWindow> mUserControlWindows = null;
        private List<OpenGLHWndWindow> mHwndWindows = null;
        OpenGLHWndWindow newWindow;

        public MainWindow()
        {
            InitializeComponent();
            this.WindowStartupLocation = WindowStartupLocation.CenterOwner;

            this.Closing += new System.ComponentModel.CancelEventHandler(MainWindow_Closing);
            AllocateLists();

            this.Loaded += new RoutedEventHandler(MainWindow_Loaded);
        }

        void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            newWindow = new OpenGLHWndWindow();
            newWindow.Closing += new System.ComponentModel.CancelEventHandler(newWindow_Closing);
            if (null != newWindow && null != mHwndWindows)
            {
                newWindow.Loaded += new RoutedEventHandler(newWindow_Loaded);
                newWindow.Show();
                mHwndWindows.Add(newWindow);
            }
        }


        void MainWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            CloseAllWindows();
        }

        private void AllocateLists()
        {
            mUserControlWindows = new List<OpenGLUserControlWindow>();
            mHwndWindows = new List<OpenGLHWndWindow>();
        }

        private void CloseAllWindows()
        {
            if (null != mUserControlWindows)
            {
                foreach (OpenGLUserControlWindow windowRover in mUserControlWindows)
                    windowRover.Close();
            }

            if (null != mHwndWindows)
            {
                foreach (OpenGLHWndWindow windowRover in mHwndWindows)
                    windowRover.Close();
            }

            AllocateLists();
        }

        void newWindow_Loaded(object sender, RoutedEventArgs e)
        {
            this.Hide();

        }

        void newWindow_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
}
