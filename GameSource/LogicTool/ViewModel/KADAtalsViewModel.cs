using FreeImageAPI;
using LogicCommon;
using LogicTool.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Media.Imaging;

namespace LogicTool.ViewModel
{
    public class KADAtalsViewModel : ViewModelBase
    {
        public static KADAtalsViewModel Instance
        {
            get;
            private set;
        }

        private ObservableCollection<PieceInfo> m_pieceList;

        public ObservableCollection<PieceInfo> pieceList
        {
            get
            {
                return m_pieceList;
            }
            set
            {
                m_pieceList = value;
                NotifyPropertyChanged("pieceList");
            }
        }

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
                NotifyPropertyChanged("pieceSelection");
            }
        }


        private bool isLoad = false;

        private readonly BackgroundWorker worker = new BackgroundWorker();

        public WPFOpenGLLib.OpenGLHwnd m_OpenGl2Md2;


        public KADAtalsViewModel()
        {
            m_pieceList = new ObservableCollection<PieceInfo>();

            m_pieceList.CollectionChanged += m_pieceList_CollectionChanged;
            Instance = this;
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

                        node.Width = fib.Width;
                        node.Height = fib.Height;

                        pieceList.Add(node);
                        text = reader.ReadLine();
                    }
                }
                catch(Exception e)
                {
                    MessageBox.Show(e.ToString());
                }
                

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

                m_OpenGl2Md2.SetNewPiece(m.TextureName);


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
