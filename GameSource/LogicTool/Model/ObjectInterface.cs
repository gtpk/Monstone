#region 어셈블리 OpenGLManagedCpp, Version=1.0.6207.312, Culture=neutral, PublicKeyToken=null
// OpenGLManagedCpp.dll
#endregion


#if TEST
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

//blend 에서 에러 나서 막기위해서 만듦
namespace LogicCommon
{
    [StructLayout(LayoutKind.Sequential)]
    public class ObjectInterface : INotifyPropertyChanged
    {

        public string AlphaTextureName;
        public string ObjectName;
        public int CurrentName;
        public float Height;
        public string ModelName;
        public ValueType Rotation;
        public float Scale;
        public string TextureName;
        public ValueType Trance;
        public float Width;

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (this.PropertyChanged != null)
                this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }

    //[StructLayout(LayoutKind.Sequential)]
    //public class SelectObjectInterface : ObjectInterface
    //{
    //    public static SelectObjectInterface GetInstance() { return null; }
    //}
}
#endif