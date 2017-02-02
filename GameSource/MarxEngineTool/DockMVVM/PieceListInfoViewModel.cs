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
    public class PieceListInfoViewModel : ToolViewModel
    {
        public PieceListInfoViewModel()
            :base("Piece List")
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

        public const string ToolContentId = "PieceListTool";

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
                return PieceListInfoViewModel.m_pieceList;
            }
            set
            {
                PieceListInfoViewModel.m_pieceList = value;
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
            if ((bool)DesignerProperties.IsInDesignModeProperty.GetMetadata(typeof(DependencyObject)).DefaultValue)
            {
                return;
            }
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

                if (f.FullName.Contains("AtlasGen")) //아틀라스는 예외
                    continue;

                String AlphaPath = f.FullName.ToLower();

                PieceInfo node = new PieceInfo();

                node.TextureFilePath = f.FullName;

                if (f.FullName.Contains("_a."))
                    continue;

                AlphaPath = AlphaPath.Replace("_c.", "_a.");


                bool AlphaEnable = false;






                node.AlphaTextureFilePath = AlphaPath;


                if (node.TextureFilePath.ToLower() == node.AlphaTextureFilePath)
                    AlphaEnable = false;
                else
                    AlphaEnable = true;

                FileInfo file = new FileInfo(AlphaPath);
                if (!file.Exists)
                    AlphaEnable = false;

                FreeImageBitmap Alphafib;
                try
                {
                    Alphafib = new FreeImageBitmap(node.AlphaTextureFilePath);
                }
                catch
                {
                    continue;
                }

                /*
                BitmapSource Alphasource =
                System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap
                (
                    Alphafib.GetHbitmap(), IntPtr.Zero, Int32Rect.Empty,
                    System.Windows.Media.Imaging.BitmapSizeOptions.FromEmptyOptions()
                );
                BitmapSourceList.Add(Alphasource);
                */




                FreeImageBitmap fib = new FreeImageBitmap(node.TextureFilePath);

                if (AlphaEnable)
                {
                    for (int y = 0; y < Alphafib.Height; y++)
                    {
                        for (int x = 0; x < Alphafib.Width; x++)
                        {
                            Color tempColor = Alphafib.GetPixel(x, y);
                            Color ColorMap = fib.GetPixel(x, y);



                            int Red = Abs255Color(255 - tempColor.R);
                            int Blue = Abs255Color(255 - tempColor.G);
                            int Green = Abs255Color(255 - tempColor.B);

                            Color swtch = Color.FromArgb(
                                Abs255Color(tempColor.R),
                                Abs255Color(ColorMap.R - Red),
                                Abs255Color(ColorMap.G - Green),
                                Abs255Color(ColorMap.B - Blue));
                            fib.SetPixel(x, y, swtch);
                        }
                    }
                }


                BitmapSource source =
                System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap
                (
                    fib.GetHbitmap(), IntPtr.Zero, Int32Rect.Empty,
                    System.Windows.Media.Imaging.BitmapSizeOptions.FromEmptyOptions()
                );

                node.BitmapSource = source;



                node.Width = fib.Width;
                node.Height = fib.Height;
                // string savedname = AlphaPath.Replace("_a.", ".");
                // try
                // {
                //     fib.Save(savedname);
                // }
                // catch(Exception e)
                // {
                //     MessageBox.Show(e.ToString());
                //     continue;
                // }
                m_pieceList.Add(node);


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
            PieceInfo m = pieceSelection;
            string TextureName = m.TextureName;
            int pos = TextureName.LastIndexOf('.');
            string extestion = TextureName.Substring(pos);

            if (m.AlphaTextureFileName == "" || m.AlphaTextureFileName == m.TextureName)
                Workspace.This.OpenGl2Md2.SetNewPiece(((float)m.Width), ((float)m.Height), m.TextureName);
            else
            {
                if (extestion == ".png")
                    Workspace.This.OpenGl2Md2.SetNewPiece(((float)m.Width), ((float)m.Height), m.TextureName);
                else
                    Workspace.This.OpenGl2Md2.SetNewPiece(((float)m.Width), ((float)m.Height), m.TextureName, m.AlphaTextureFileName);
            }
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
