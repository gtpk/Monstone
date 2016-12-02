using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;


namespace LogicTool
{
    
   // public delegate CallViewModel();
    public delegate void nonStaticCall(object o);
    public class PieceCommand : ICommand
    {
        public event nonStaticCall StaticExecute;

        private static PieceCommand staticcommand;

        public static PieceCommand GetInstance()
        {
            if (staticcommand == null)
            {
                staticcommand = new PieceCommand();
            }

            return staticcommand;
        }

        private PieceCommand()
        {
        }

        public bool CanExecute(object parameter)
        {
            return true;
        }

        public event EventHandler CanExecuteChanged;

        public void Execute(object parameter)
        {
            if (StaticExecute != null)
                StaticExecute(parameter);
        }
    }
}
