using LogicTool.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace LogicTool.Virtual_Interface
{
    public class CommandBase : ICommand
    {
        public ViewModelBase ChildObj;

        public CommandBase(ViewModelBase Mother)
        {
            ChildObj = Mother;
        }

        public bool CanExecute(object parameter)
        {
            if (ChildObj == null)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        public event EventHandler CanExecuteChanged;

        public void Execute(object parameter)
        {
            (ChildObj as ViewModelBase).Excute(parameter);
        }
    }
}
