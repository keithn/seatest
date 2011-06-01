using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;

namespace SeaTest
{
    public class SeaTestViewModel : Observable
    {
        private FileSystemWatcher _watcher;
        public ObservableCollection<Fixture> Suite { get; set; }

        public SeaTestViewModel()
        {
            Suite = new ObservableCollection<Fixture>();            
            Update();          
        }

        private static void Save()
        {
            Properties.Settings.Default.Save();
        }

        public string ExecutableUnderTest
        {
            get { return Properties.Settings.Default.ExecutableUnderTest; }
            set { Properties.Settings.Default.ExecutableUnderTest = value; Save(); OnPropertyChanged("ExecutableUnderTest"); Update();}
        }

        private void Update()
        {
            MonitorTarget();
            UpdateTests();
        }

        private bool HasValidTarget
        {
            get { return File.Exists(ExecutableUnderTest); }
        }

        private void Execute(string commandLine, Action<string> responseHandler)
        {
            ThreadPool.QueueUserWorkItem(w => ExecuteProcess(commandLine, responseHandler));            
        }

        private string _output;
        private object _executeProcessLock = new object();

        private void ExecuteProcess(string commandLine, Action<string> responseHandler)
        {
            lock(_executeProcessLock)
            {
                var p = new Process();
                try
                {
                    _output = "";
                    var startInfo = new ProcessStartInfo
                                        {
                                            CreateNoWindow = true,
                                            UseShellExecute = false,
                                            Arguments = commandLine,
                                            FileName = ExecutableUnderTest,
                                            WindowStyle = ProcessWindowStyle.Hidden,
                                            RedirectStandardOutput = true
                                        };

                    p.StartInfo = startInfo;
                    p.OutputDataReceived += CaptureOutput;
                    p.Start();
                    p.BeginOutputReadLine();
                    p.WaitForExit();
                    responseHandler(_output);
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());
                }                
            }         
        }
        
        private void CaptureOutput(object sender, DataReceivedEventArgs e)
        {
            _output += e.Data +"\r\n";
        }

        private void UpdateTests()
        {
            Suite.Clear();
            if (HasValidTarget) Execute("-d", ParseTestList);
        }

        private void ParseTestList(string result)
        {
            var lines = result.Split(new []{'\r','\n'}, StringSplitOptions.RemoveEmptyEntries);
            foreach(var test in lines)
            {
                var entry = test.Split(new char[] {','}, StringSplitOptions.RemoveEmptyEntries);
                if(entry.Length == 2)
                {
                    var fixture = GetFixtureByPath(entry[0]);
                    fixture.AddTest(entry[1]);
                }
            }
        }

        private Fixture GetFixtureByPath(string s)
        {
            var fixture = Suite.Where(f => f.Path == s).FirstOrDefault();
            if(fixture == null )
            {
                fixture = new Fixture() { Path = s, Name = Path.GetFileNameWithoutExtension(s)};
                Suite.Add(fixture);
            }
            return fixture;
        }

        private string _testOutput;
        public string TestOutput
        {
            get { return _testOutput; }
            set { _testOutput = value; OnPropertyChanged("TestOutput");}
        }

        private void ParseTestRun(string result)
        {
            TestOutput = result;
        }

        private void MonitorTarget()
        {
            if(!HasValidTarget) return;

            var directory = Path.GetDirectoryName(ExecutableUnderTest);
            var filename = Path.GetFileName(ExecutableUnderTest);
            _watcher = new FileSystemWatcher
                           {
                               Path = directory,
                               NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite
                                              | NotifyFilters.FileName | NotifyFilters.DirectoryName,
                               Filter = filename
                           };
            _watcher.Created += ExecutableChanged;
            _watcher.Changed += ExecutableChanged;
            _watcher.EnableRaisingEvents = true;
        }

        private void ExecutableChanged(object sender, FileSystemEventArgs e)
        {
                                
        }

        public void Run()
        {
            if(HasValidTarget) Execute("", ParseTestRun);
        }
    }
}
