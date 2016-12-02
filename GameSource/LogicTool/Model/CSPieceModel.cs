using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Windows.Media.Media3D;

namespace LogicTool
{
    public class CSPieceModel : INotifyPropertyChanged
    {
        private String filename;
        public String TextureName
        {
            get
            {
                return filename;
            }
            set
            {

                filename = value;
                NotifyPropertyChanged("TextureName");
            }
        }

        private float m_scale;

        public float Scale
        {
            get
            {
                return m_scale;
            }
            set
            {
                m_scale = value;
                NotifyPropertyChanged("Scale");
            }
        }

        private int m_currentName;

        public int currentName
        {
            get
            {
                return m_currentName;
            }
            set
            {
                m_currentName = value;
                NotifyPropertyChanged("currentName");
            }
        }

        private float m_Width;

        public float Width
        {
            get
            {
                return m_Width;
            }
            set
            {
                m_Width = value;
                NotifyPropertyChanged("Width");
            }
        }
      
        private float m_Height;

        public float Height
        {
            get
            {
                return m_Height;
            }
            set
            {
                m_Height = value;
                NotifyPropertyChanged("Height");
            }
        }

        private Vector3D m_Rotation;

        private Vector3D Rotation
        {
            get
            {
                return m_Rotation;
            }
            set
            {
                m_Rotation = value;
                NotifyPropertyChanged("Rotation");
            }
        }

        private Vector3D m_Trance;

        public Vector3D Trance
        {
            get
            {
                return m_Trance;
            }
            set
            {
                m_Trance = value;
                NotifyPropertyChanged("Trance");
            }
        }

        #region INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        private void NotifyPropertyChanged(string info)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(info));
            }
        }

        #endregion
    }
}
