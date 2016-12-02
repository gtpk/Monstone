using FreeImageAPI;
using Paloma;
using System;
using System.Collections.Generic;
using System.ComponentModel;
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
	/// AlphaTextureView.xaml에 대한 상호 작용 논리
	/// </summary>
	public partial class AlphaTextureView : UserControl
	{
        public static readonly DependencyProperty TgaAlphaImageUriProperty =
           DependencyProperty.Register("TgaAlphaImageUri", typeof(String), typeof(AlphaTextureView), new FrameworkPropertyMetadata(new PropertyChangedCallback(OnUserNamePropertyChanged)));

        public String TgaAlphaImageUri
        {
            get 
            {
                if (DesignerProperties.GetIsInDesignMode(this))
                {
                    return (string)GetValue(TgaAlphaImageUriProperty); 
                }
                return "DesignModeExample";
            }
            set 
            {
                if (DesignerProperties.GetIsInDesignMode(this))
                {
                    SetValue(TgaAlphaImageUriProperty, value);
                }
            }
        }

        private static void OnUserNamePropertyChanged(DependencyObject iobject, DependencyPropertyChangedEventArgs e)
        {
           
            AlphaTextureView control = iobject as AlphaTextureView;
            String value = (String)iobject.GetValue(TgaAlphaImageUriProperty);
            control.tb_Name.Text = value;
            if (value == "")
                return;
            FreeImageBitmap fib = new FreeImageBitmap(value);

            control.i_Targa.Source = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(fib.GetHbitmap(), IntPtr.Zero, Int32Rect.Empty,
            System.Windows.Media.Imaging.BitmapSizeOptions.FromEmptyOptions());
        }

		public AlphaTextureView()
		{
			this.InitializeComponent();
		}
	}
}