using System;
using System.ComponentModel;
using System.Windows.Threading;

namespace SeaTest
{
    public abstract class Observable : INotifyPropertyChanged
    {
        private Dispatcher _dispatcher;
        protected Observable()
        {
            _dispatcher = Dispatcher.CurrentDispatcher;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            var handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, e);
            }
        }

        protected void OnPropertyChanged(string propertyName)
        {
            OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
        }

        public void Invoke(Action a)
        {
            _dispatcher.Invoke(a);
        }


    }
}