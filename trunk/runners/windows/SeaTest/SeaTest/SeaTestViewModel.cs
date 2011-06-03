using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Threading;

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

        public bool Autorun
        {
            get { return Properties.Settings.Default.Autorun; }
            set { Properties.Settings.Default.Autorun = value; Save(); OnPropertyChanged("Autorun"); }
        }

        private void Update()
        {
            MonitorTarget();
            if(Autorun)
            {
                UpdateAndRun();
            }
            else
            {
                UpdateTests();    
            }            
        }

        private bool HasValidTarget
        {
            get { return File.Exists(ExecutableUnderTest); }
        }

        private void Execute(string commandLine, Action<string> responseHandler)
        {
            ThreadPool.QueueUserWorkItem(w => ExecuteProcess(commandLine, responseHandler));            
        }

        private object _executeProcessLock = new object();

        private void ExecuteProcess(string commandLine, Action<string> responseHandler)
        {
            lock(_executeProcessLock)
            {
                try
                {
                    FileSystem.RunFile(ExecutableUnderTest, commandLine, responseHandler, this);
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());
                }                
            }         
        }
        
        private void UpdateTests()
        {
            Suite.Clear();
            if (HasValidTarget) Execute("-d", result => SeaTestParser.ParseTests(result).ForEach(Suite.Add));
        }
        

        private string _testOutput;
        public string TestOutput
        {
            get { return _testOutput; }
            set { _testOutput = value; OnPropertyChanged("TestOutput");}
        }
        
        

        private void MonitorTarget()
        {
            if(!HasValidTarget) return;
            if(_watcher != null) _watcher.Dispose();
            _watcher = FileSystem.Watch(ExecutableUnderTest, ExecutableChanged);            
        }

        
        private void ExecutableChanged(object sender, FileSystemEventArgs e)
        {
              if(Autorun)
              {
                  Thread.Sleep(500);  // find a way to wait till the executable isn't being used by another process.
                  Invoke(UpdateAndRun);
              }
        }

        public void UpdateAndRun()
        {            
            UpdateTests();
            Run();
        }

        
        public void Run()
        {
            if(HasValidTarget) Execute("-v -m -k [~SEA~]", result => SeaTestParser.ParseTestRun(result, Suite));
        }
    }
}
