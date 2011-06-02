using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace SeaTest
{
    public class Fixture : Observable
    {
        public Fixture(List<Fixture> list) : this()
        {
            if(list!=null) list.Add(this);
        }

        public Fixture()
        {
            Tests = new ObservableCollection<Test>();
        }

        public string Name { get; set; }
        public string Path { get; set; }
        public ObservableCollection<Test> Tests { get; set; }

        public void AddTest(string s)
        {
            Tests.Add(new Test() { Name = s, Fixture = this});
        }
    }
}