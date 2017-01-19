using LogicCommon;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;

namespace LogicTool.ViewModel
{
    public class ImageControlTreeViewModel : ViewModelBase
    {
        static readonly ImageControlTreeViewModel DummyChild = new ImageControlTreeViewModel();


        readonly ObservableCollection<UIobjectInterface> _children;
        /// <summary>
        /// Returns the logical child items of this object.
        /// </summary>
        public ObservableCollection<UIobjectInterface> Children
        {
            get
            {
                return UIObjectTreeContator.GetInstance().Children;
            }
        }

        readonly ImageControlTreeViewModel _parent;


        bool _isSelected;


        protected ImageControlTreeViewModel(ImageControlTreeViewModel parent, bool lazyLoadChildren)
        {
            _parent = parent;

            _children = new ObservableCollection<UIobjectInterface>();

        }

        // This is used to create the DummyChild instance.
        public ImageControlTreeViewModel()
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

        public ImageControlTreeViewModel Parent
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
