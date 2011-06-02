using NUnit.Framework;
using SeaTest;

namespace SeaTestTests
{
    [TestFixture]
    public class TestParsingTestNames
    {
        [Test]
        public void TestParse()
        {
            string s = "blah, test";
            var fixtures = SeaTestParser.ParseTests(s);
            Assert.AreEqual(1, fixtures.Count);
            Assert.AreEqual("blah", fixtures[0].Name);
            Assert.AreEqual(1, fixtures[0].Tests.Count);
            Assert.AreEqual("test", fixtures[0].Tests[0].Name);
        }
        
    }

    
}