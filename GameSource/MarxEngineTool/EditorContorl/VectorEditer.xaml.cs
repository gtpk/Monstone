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
using System.Windows.Media.Media3D;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace MarxEngineTool
{
	/// <summary>
	/// VectorEditer.xaml에 대한 상호 작용 논리
	/// </summary>
	public partial class VectorEditer : UserControl
	{

        private Vector3D Vec_;

        public Vector3D Vector
        {
            get
            {
                return Vec_;
            }

            set
            {
                x_.Text = value.X.ToString();
                y_.Text = value.Y.ToString();
                z_.Text = value.Z.ToString();

                Vec_ = value;

            }
        }

		public VectorEditer()
		{
			this.InitializeComponent();
		}
	}
}