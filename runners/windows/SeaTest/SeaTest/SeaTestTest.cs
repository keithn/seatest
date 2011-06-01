using System.Collections.ObjectModel;

namespace SeaTest
{
    public class SeaTestTest : Observable
    {
        public string Name { get; set; }
        public ObservableCollection<TestFailures> Results { get; set; }

        private bool _passed = false;
        public bool Passed
        {
            get { return _passed; }
            set { _passed = value; OnPropertyChanged("Passed");}
        }
    }
}