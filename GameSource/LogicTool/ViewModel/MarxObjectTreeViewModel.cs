using LogicCommon;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace LogicTool.ViewModel
{

    public class MarxObjectTreeViewModel : ViewModelBase
    {
        static readonly MarxObjectTreeViewModel DummyChild = new MarxObjectTreeViewModel();
        

        readonly static ObservableCollection<ObjectInterface> _children = new ObservableCollection<ObjectInterface>();
        /// <summary>
        /// Returns the logical child items of this object.
        /// </summary>
        public ObservableCollection<ObjectInterface> Children
        {
            get
            {
                return ObjectTreeContator.GetInstance().Children;
            }
        }

        readonly MarxObjectTreeViewModel _parent;

        
        bool _isSelected;


        protected MarxObjectTreeViewModel(MarxObjectTreeViewModel parent, bool lazyLoadChildren)
        {
            _parent = parent;
        }

        // This is used to create the DummyChild instance.
        public MarxObjectTreeViewModel()
        {
            
        }

        /// <summary>
        /// Returns true if this object's Children have not yet been populated.
        /// </summary>
        public bool HasDummyChild
        {
            get { return this.Children.Count == 1; }
        }


        #region IsExpanded

        bool _isExpanded;


        /// <summary>
        /// Gets/sets whether the TreeViewItem 
        /// associated with this object is expanded.
        /// </summary>
        public bool IsExpanded
        {
            get { return _isExpanded; }
            set
            {
                if (value != _isExpanded)
                {
                    _isExpanded = value;
                    this.NotifyPropertyChanged("IsExpanded");
                }

                // Expand all the way up to the root.
                if (_isExpanded && _parent != null)
                    _parent.IsExpanded = true;

            }
        }

        #endregion // IsExpanded
        #region IsSelected

        /// <summary>
        /// Gets/sets whether the TreeViewItem 
        /// associated with this object is selected.
        /// </summary>
        public bool IsSelected
        {
            get { return _isSelected; }
            set
            {
                if (value != _isSelected)
                {
                    _isSelected = value;
                    this.NotifyPropertyChanged("IsSelected");
                }
            }
        }

        #endregion // IsSelected

        #region LoadChildren

        /// <summary>
        /// Invoked when the child items need to be loaded on demand.
        /// Subclasses can override this to populate the Children collection.
        /// </summary>
        protected virtual void LoadChildren()
        {
        }

        #endregion // LoadChildren

        #region Parent

        public MarxObjectTreeViewModel Parent
        {
            get { return _parent; }
        }

        #endregion // Parent

        #region INotifyPropertyChanged Members

        // ObjectInterface에서 선언함
        //public event PropertyChangedEventHandler PropertyChanged;
        //
        //protected virtual void OnPropertyChanged(string propertyName)
        //{
        //    if (this.PropertyChanged != null)
        //        this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        //}

        #endregion // INotifyPropertyChanged Members
    }
}
