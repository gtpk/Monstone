using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Media.Imaging;

namespace LogicTool.Model
{
    public class KardatalsList
    {
        public Dictionary<string, BitmapSource> KardList;

        private KardatalsList()
        {
            KardList = new Dictionary<string, BitmapSource>();
        }

        private static KardatalsList inst;
        public static KardatalsList Getinstance()
        {
            if (inst == null)
                inst = new KardatalsList();
            return inst;
        }

    }
}
