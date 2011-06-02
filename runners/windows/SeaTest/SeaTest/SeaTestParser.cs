using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace SeaTest
{
    public static class SeaTestParser
    {
        public static string[] SplitCommaSepatedValues(string s)
        {
            return s.Split(new[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
        }

        public static string[] SplitIntoLines(string s)
        {
            return s.Split(new[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
        }

        public static void ParseTestRun(string result, IEnumerable<Fixture> fixtures)
        {
            if(fixtures == null) return;
            var lines = SplitIntoLines(result).Where(l => l.StartsWith("[~SEA~]")).Select(l => l.Remove(0, 7)).ToList();
            foreach (var testResultLine in lines)
            {
                var values = SplitCommaSepatedValues(testResultLine);
                if (values.Length == 4)
                {
                    var fixturePath = values[0].Trim();
                    var testName = values[1].Trim();
                    var lineNumber = values[2].Trim();
                    var testResult = values[3].Trim();

                    var fixture = fixtures.FirstOrDefault(f => f.Path == fixturePath);
                    if (fixture != null)
                    {                        
                        var test = fixture.Tests.FirstOrDefault(t => t.Name == testName);
                        if (test != null)
                        {
                            var passed = (testResult == "Passed");
                            test.Passed = test.HasRun ? test.Passed && passed : passed;
                            test.HasRun = true;
                        }
                    }
                }
            }
        }
       

        public static List<Fixture> ParseTests(string s)
        {
            var fixtures = new List<Fixture>();

            var lines = SplitIntoLines(s);
            foreach (var test in lines)
            {
                var entry = SplitCommaSepatedValues(test);
                if (entry.Length == 2)
                {
                    var fixturePath = entry[0].Trim();
                    string testName = entry[1].Trim();
                    var fixture = fixtures.FirstOrDefault(f => f.Path == fixturePath) ?? new Fixture(fixtures) { Path = fixturePath, Name = Path.GetFileNameWithoutExtension(fixturePath) };
                    fixture.AddTest(testName);
                }
            }
            return fixtures;
        }
    }
}