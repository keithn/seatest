using System.Collections.ObjectModel;

namespace SeaTest
{
    public class SeaTestFixture : Observable
    {
        public SeaTestFixture()
        {
            Tests = new ObservableCollection<SeaTestTest>();
        }

        public string Name { get; set; }
        public string Path { get; set; }
        public ObservableCollection<SeaTestTest> Tests { get; set; }

        public void AddTest(string s)
        {
            Tests.Add(new SeaTestTest() { Name = s});
        }
    }
}