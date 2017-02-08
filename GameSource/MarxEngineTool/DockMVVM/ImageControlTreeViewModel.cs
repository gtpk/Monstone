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
    public class ImageControlTreeViewModel : ToolViewModel
    {
        public ImageControlTreeViewModel()
            :base("Image Control Tree")
        {
            Workspace.This.ActiveDocumentChanged += new EventHandler(OnActiveDocumentChanged);
            ContentId = ToolContentId;

            BitmapImage bi = new BitmapImage();
            bi.BeginInit();
            bi.UriSource = new Uri("pack://application:,,/Images/property-blue.png");
            bi.EndInit();
            IconSource = bi;
           

            RaisePropertyChanged("Children");
        }

        public const string ToolContentId = "ImageControlTree";

        void OnActiveDocumentChanged(object sender, EventArgs e)
        {
            RaisePropertyChanged("Children");
        }

        private void m_pieceList_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            RaisePropertyChanged("Children");
        }


        #region pieceList
        public ObservableCollection<UIobjectInterface> Children
        {
            get
            {
                return UIObjectTreeContator.GetInstance().Children;
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

    }
}
