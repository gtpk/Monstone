using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace LogicTool.Model
{
    public class PieceInfo : INotifyPropertyChanged
    {
        private String _TextureFilePath;
        public String TextureFilePath
        {
            get
            {
                return _TextureFilePath;
            }
            set
            {

                _TextureFilePath = value;

                String[] paths = TextureFilePath.Split('\\');

                TextureName = paths[paths.Length-1];

                NotifyPropertyChanged("TextureFilePath");
            }
        }

        private String _TextureName;
        public String TextureName
        {
            get
            {
                return _TextureName;
            }
            set
            {

                _TextureName = value;
                NotifyPropertyChanged("TextureName");
            }
        }



        private String _AlphaTextureFilePath;
        public String AlphaTextureFilePath
        {
            get
            {
                return _AlphaTextureFilePath;
            }
            set
            {

                _AlphaTextureFilePath = value;

                String[] paths = _AlphaTextureFilePath.Split('\\');

                AlphaTextureFileName = paths[paths.Length - 1];

                NotifyPropertyChanged("AlphaTextureFilePath");
            }
        }

        private String _AlphaTextureFileName;
        public String AlphaTextureFileName
        {
            get
            {
                return _AlphaTextureFileName;
            }
            set
            {

                _AlphaTextureFileName = value;
                NotifyPropertyChanged("AlphaTextureFileName");
            }
        }


        private int _Width;
        public int Width
        {
            get
            {
                return _Width;
            }
            set
            {

                _Width = value;
                NotifyPropertyChanged("Width");
            }
        }

        private int _Height;
        public int Height
        {
            get
            {
                return _Height;
            }
            set
            {

                _Height = value;
                NotifyPropertyChanged("Height");
            }
        }

        private BitmapSource _BitmapSource;
        public BitmapSource BitmapSource
        {
            get
            {
                return _BitmapSource;
            }
            set
            {

                _BitmapSource = value;
                NotifyPropertyChanged("BitmapSource");
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
