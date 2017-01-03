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
        
        public SelectObjectInterface piecemodel
        {
            get
            {
                return SelectObjectInterface.GetInstance();
            }

        }

        public PieceAddViewModel()
        {
            piecemodel.PropertyChanged += new PropertyChangedEventHandler(piecemodel_PropertyChanged);

            Instance = this;
        }

        void piecemodel_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            NotifyPropertyChanged("piecemondel." + e.PropertyName);
        }



    }
}
