using FreeImageAPI;
using Paloma;
using System;
using System.Collections.Generic;
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

namespace MarxEngineTool
{
	/// <summary>
	/// SourceTextureView.xaml에 대한 상호 작용 논리
	/// </summary>
	public partial class SourceTextureView : UserControl
	{

        public static readonly DependencyProperty TgaImageUriProperty =
           DependencyProperty.Register("TgaImageUri", typeof(String), typeof(SourceTextureView), new FrameworkPropertyMetadata(new PropertyChangedCallback(OnUserNamePropertyChanged)));

        public String TgaImageUri
        {
            get 
            {
                return (string)GetValue(TgaImageUriProperty); 
            }
            set 
            {
                SetValue(TgaImageUriProperty, value);
               
            }
        }

		public SourceTextureView()
		{
			this.InitializeComponent();
		}

        private static void OnUserNamePropertyChanged(DependencyObject iobject, DependencyPropertyChangedEventArgs e)
        {
            SourceTextureView control = iobject as SourceTextureView;
            String value = (String)iobject.GetValue(TgaImageUriProperty);


            control.tb_Name.Text = value;

            if (value == "")
                return;

            FreeImageBitmap fib = new FreeImageBitmap(value);

            control.i_Targa.Source = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(fib.GetHbitmap(), IntPtr.Zero, Int32Rect.Empty,
            System.Windows.Media.Imaging.BitmapSizeOptions.FromEmptyOptions());
        }
	}
}