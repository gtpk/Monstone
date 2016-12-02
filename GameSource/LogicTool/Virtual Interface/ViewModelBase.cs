using LogicTool.Virtual_Interface;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LogicTool.ViewModel
{
    public class ViewModelBase : INotifyPropertyChanged
    {

        #region INotifyPropertyChanged
        public event PropertyChangedEventHandler PropertyChanged;

        public void NotifyPropertyChanged(string info)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(info));
            }
        }

        public CommandBase Command
        {
            get 
            { 
                return new CommandBase(this);
            }
        }

        #endregion

        public virtual void Excute(object param)
        {
        }

    }
}
