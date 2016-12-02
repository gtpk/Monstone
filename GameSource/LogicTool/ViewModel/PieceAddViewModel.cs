using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.Windows.Input;
using LogicCommon;
using LogicTool.ViewModel;

namespace LogicTool
{
    public class PieceAddViewModel : ViewModelBase
    {


        public static PieceAddViewModel Instance
        {
            get;
            private set;
        }

        private SelectObjectInterface m_piecemodel;

        public SelectObjectInterface piecemodel
        {
            get
            {
                return m_piecemodel;
            }
            set
            {
                m_piecemodel = value;
                NotifyPropertyChanged("piecemodel");
            }

        }

        public PieceAddViewModel()
        {
            piecemodel = SelectObjectInterface.GetInstance();
            piecemodel.PropertyChanged += new PropertyChangedEventHandler(piecemodel_PropertyChanged);

            Instance = this;
        }

        void piecemodel_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            NotifyPropertyChanged("piecemondel." + e.PropertyName);
        }



    }
}
