using System.Collections.ObjectModel;

namespace SeaTest
{
    public class SeaTestTest : Observable
    {
        public string Name { get; set; }
        public ObservableCollection<TestFailures> Results { get; set; }
    }
}