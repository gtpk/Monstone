using LogicTool.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LogicCommon;
using LogicTool.ViewModel;
using System.IO;
using Paloma;
using System.Windows.Media.Imaging;
using System.Windows;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using FreeImageAPI;
using System.Threading;
using System.Windows.Threading;
using System.ComponentModel;
using System.Xml;

namespace LogicTool.ViewModel
{
    public class PieceListViewModel : ViewModelBase
    {
        private static PieceListViewModel _Instance;

        public static PieceListViewModel Instance
        {
            get
            {
                if (PieceListViewModel._Instance == null)
                    PieceListViewModel._Instance = new PieceListViewModel();
                return PieceListViewModel._Instance;
            }
        }

        private ObservableCollection<PieceInfo> m_pieceList;

        public ObservableCollection<PieceInfo> pieceList
        {
            get
            {
                return PieceListViewModel.Instance.m_pieceList;
            }
            set
            {
                PieceListViewModel.Instance.m_pieceList = value;
                NotifyPropertyChanged("pieceList");
            }
        }

        private PieceInfo m_pieceSelection;

        public PieceInfo pieceSelection
        {
            get
            {
                return PieceListViewModel.Instance.m_pieceSelection;
            }
            set
            {
                PieceListViewModel.Instance.m_pieceSelection = value;
                NotifyPropertyChanged("pieceSelection");
            }
        }


        private bool isLoad = false;

        private readonly BackgroundWorker worker = new BackgroundWorker();

        public static WPFOpenGLLib.OpenGLHwnd m_OpenGl2Md2;

        
        public PieceListViewModel()
        {
            m_pieceList = new ObservableCollection<PieceInfo>();
            m_pieceList.CollectionChanged += m_pieceList_CollectionChanged;
            //OnetimeInit();
        }

        private void m_pieceList_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            NotifyPropertyChanged("pieceList");
            //throw new NotImplementedException();
        }

        
        private void OnetimeInit()
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
                foreach (PieceInfo p in pieceList)
                {
                    if (p.AlphaTextureFilePath == f.FullName || p.TextureFilePath == f.FullName)
                    {
                        isFind = true;
                        break;
                    }
                }

                if (isFind) //찾았는가 중복은 버린다!
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


                            fib.SetPixel(x, y, Color.FromArgb(
                                Abs255Color(ColorMap.R - Red),
                                Abs255Color(ColorMap.G - Green),
                                Abs255Color(ColorMap.B - Blue)));
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
                pieceList.Add(node);

                
            }
        }

        public override void Excute(object param) 
        {
            if (param == null)
                return;

            string sparam = param.ToString();

            if (sparam == "Load")
            {
                /*
                worker.DoWork += worker_DoWork;
                //Thread ImageLoadeThread = new Thread(new ThreadStart(OnetimeInit));
                //ImageLoadeThread.Start();
                worker.RunWorkerAsync();*/
                OnetimeInit();
            }
            else if (sparam == "MakePieceInfo")
            {
                if (pieceSelection == null)
                    return;

                PieceInfo m = pieceSelection;
                string TextureName = m.TextureName;
                int pos = TextureName.LastIndexOf('.');
                string extestion = TextureName.Substring(pos);

                if (m.AlphaTextureFileName == "" || m.AlphaTextureFileName == m.TextureName)
                    m_OpenGl2Md2.SetNewPiece(((float)m.Width), ((float)m.Height), m.TextureName);
                else
                {
                    if(extestion == ".png")
                        m_OpenGl2Md2.SetNewPiece(((float)m.Width), ((float)m.Height), m.TextureName);
                    else
                        m_OpenGl2Md2.SetNewPiece(((float)m.Width), ((float)m.Height), m.TextureName, m.AlphaTextureFileName);
                }
                    
                
            }
            else if (param is PieceInfo)
            {
                PieceInfo m = (PieceInfo)param;

                pieceSelection = m;
            }

        }

        private void worker_DoWork(object sender, DoWorkEventArgs e)
        {
            OnetimeInit();
        }

        public int Abs255Color(int value)
        {
            if (value < 0)
                value = 0;
            if (value > 255)
                value = 255;
            return value;
        }
        
    }
}
