/************************************************************************

   AvalonDock

   Copyright (C) 2007-2013 Xceed Software Inc.

   This program is provided to you under the terms of the New BSD
   License (BSD) as published at http://avalondock.codeplex.com/license 

   For more features, controls, and fast professional support,
   pick up AvalonDock in Extended WPF Toolkit Plus at http://xceed.com/wpf_toolkit

   Stay informed: follow @datagrid on Twitter or Like facebook.com/datagrids

  **********************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Media.Imaging;
using System.Collections.ObjectModel;
using LogicTool.Model;
using System.ComponentModel;
using LogicTool.Virtual_Interface;
using LogicCommon;
using System.Windows;
using FreeImageAPI;
using System.Drawing;
using System.Windows.Input;

namespace AvalonDock.MVVMTestApp
{
    public class UIObjectListInfoViewModel : ToolViewModel
    {
        public UIObjectListInfoViewModel()
            :base("UI Object List")
        {
            Workspace.This.ActiveDocumentChanged += new EventHandler(OnActiveDocumentChanged);
            ContentId = ToolContentId;

            BitmapImage bi = new BitmapImage();
            bi.BeginInit();
            bi.UriSource = new Uri("pack://application:,,/Images/property-blue.png");
            bi.EndInit();
            IconSource = bi;

            m_pieceList.CollectionChanged += m_pieceList_CollectionChanged;
            OnetimeInit();

            RaisePropertyChanged("pieceList");
        }

        public const string ToolContentId = "UIObjectList";

        void OnActiveDocumentChanged(object sender, EventArgs e)
        {
        }

        private void m_pieceList_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            RaisePropertyChanged("pieceList");
        }


        #region pieceList
        private static ObservableCollection<PieceInfo> m_pieceList = new ObservableCollection<PieceInfo>();

        public ObservableCollection<PieceInfo> pieceList
        {
            get
            {
                return UIObjectListInfoViewModel.m_pieceList;
            }
            set
            {
                UIObjectListInfoViewModel.m_pieceList = value;
                RaisePropertyChanged("pieceList");
            }
        }
        #endregion

        #region pieceList
        private PieceInfo m_pieceSelection;

        public PieceInfo pieceSelection
        {
            get
            {
                return m_pieceSelection;
            }
            set
            {
                m_pieceSelection = value;
                RaisePropertyChanged("pieceSelection");
            }
        }
        #endregion


        private static bool isLoad = false;

        private static void OnetimeInit()
        {
            if (isLoad)
                return;
            isLoad = true;

            DirectoryInfo di = new DirectoryInfo(
                ProjectSettingValuesInterface.GetInstance().ProjectPath + @"\asset");

            bool isFind = false;
            foreach (FileInfo f in di.GetFiles())
            {
                isFind = false;
                foreach (PieceInfo p in m_pieceList)
                {
                    if (p.AlphaTextureFilePath == f.FullName || p.TextureFilePath == f.FullName)
                    {
                        isFind = true;
                        break;
                    }
                }

                if (isFind) //찾았는가 중복은 버린다!
                    continue;

                if (f.FullName.Contains(".txt"))
                    continue;

                if (!f.FullName.Contains("AtlasGen"))
                    continue;

                FreeImageBitmap fib = new FreeImageBitmap(f.FullName);


                try
                {


                    string atlaspath = f.FullName;
                    atlaspath = atlaspath.Replace(".png", ".txt");


                    StreamReader reader = File.OpenText(atlaspath);

                    string text = reader.ReadLine();

                    while (text != null)
                    {
                        AtlasObj obj = new AtlasObj();
                        string[] bits = text.Split(' ');
                        string Name = bits[0]; // 값을 저장하기
                        obj.UV_X = float.Parse(bits[1]);
                        obj.UV_Y = float.Parse(bits[2]);

                        obj.UVB_X = float.Parse(bits[3]);
                        obj.UVB_Y = float.Parse(bits[4]);

                        obj.Width = float.Parse(bits[5]);
                        obj.Height = float.Parse(bits[6]);

                        int UVB_X = (int)(fib.Width * obj.UVB_X);
                        int UVB_Y = (int)(fib.Height * (1 - obj.UV_Y));

                        int UV_X = (int)(fib.Width * obj.UV_X);
                        int UV_Y = (int)(fib.Height * (1 - obj.UVB_Y));

                        FreeImageBitmap atalsimage = new FreeImageBitmap((int)obj.Width, (int)obj.Height);



                        for (int x = 0; x + UV_X < UVB_X; x++)
                        {
                            for (int y = 0; y + UV_Y < UVB_Y; y++)
                            {
                                Color tempColor = fib.GetPixel(x + UV_X, y + UV_Y);
                                atalsimage.SetPixel(x, y, tempColor);
                            }
                        }
                        BitmapSource source =
                        System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap
                        (
                            atalsimage.GetHbitmap(), IntPtr.Zero, Int32Rect.Empty,
                            System.Windows.Media.Imaging.BitmapSizeOptions.FromEmptyOptions()
                        );

                        PieceInfo node = new PieceInfo();
                        node.TextureName = Name;
                        node.TextureFilePath = Name;
                        node.BitmapSource = source;
                        KardatalsList.Getinstance().KardList[Name] = source;
                        node.Width = fib.Width;
                        node.Height = fib.Height;

                        m_pieceList.Add(node);
                        text = reader.ReadLine();
                    }
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());
                }


            }

        }

        #region MakePieceInfo
        RelayCommand _MakePieceInfo = null;
        public ICommand MakePieceInfo
        {
            get
            {
                if (_MakePieceInfo == null)
                {
                    _MakePieceInfo = new RelayCommand((p) => OnMakePieceInfo(), (p) => CanMakePieceInfo());
                }

                return _MakePieceInfo;
            }
        }

        private bool CanMakePieceInfo()
        {
            if (pieceSelection == null)
                return false;
            return true;
        }

        private void OnMakePieceInfo()
        {
            if (pieceSelection == null)
                return;

            PieceInfo m = pieceSelection;

            Workspace.This.OpenGl2Md2.SetNewPiece(m.TextureName);
        }
        #endregion

        #region SelectCommand
        RelayCommand _SelectCommand = null;
        public ICommand SelectCommand
        {
            get
            {
                if (_SelectCommand == null)
                {
                    _SelectCommand = new RelayCommand((p) => OnSelect(p), (p) => CanSelect(p));
                }

                return _SelectCommand;
            }
        }

        private bool CanSelect(object parameter)
        {
            if(typeof(PieceInfo) == parameter.GetType())
                return true;
            return false;
        }

        private void OnSelect(object parameter)
        {
            pieceSelection = (PieceInfo)parameter;
        }

        #endregion

        public static int Abs255Color(int value)
        {
            if (value < 0)
                value = 0;
            if (value > 255)
                value = 255;
            return value;
        }
    }
}
