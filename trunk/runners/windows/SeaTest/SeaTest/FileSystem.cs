using System;
using System.Diagnostics;
using System.IO;
using System.Windows;

namespace SeaTest
{
    public static class FileSystem
    {
        public static FileSystemWatcher Watch(string path, FileSystemEventHandler handler)
        {
            var directory = Path.GetDirectoryName(path);
            var filename = Path.GetFileName(path);
            var fileSystemWatcher = new FileSystemWatcher
                                        {
                                            Path = directory,
                                            NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite
                                                           | NotifyFilters.FileName | NotifyFilters.DirectoryName,
                                            Filter = filename
                                        };
            fileSystemWatcher.Created += handler;
            fileSystemWatcher.Changed += handler;
            fileSystemWatcher.EnableRaisingEvents = true;
            return fileSystemWatcher;
        }

        public static void RunFile(string path, string arguments, Action<String> resultHandler, Observable dispatcher)
        {
            var p = new Process();
            var startInfo = new ProcessStartInfo
                                {
                                    CreateNoWindow = true,
                                    UseShellExecute = false,
                                    Arguments = arguments,
                                    FileName = path,
                                    WindowStyle = ProcessWindowStyle.Hidden,
                                    RedirectStandardOutput = true
                                };

            p.StartInfo = startInfo;
            var output = "";
            p.OutputDataReceived += delegate(object o, DataReceivedEventArgs e) { output += e.Data + "\r\n"; };
            p.Start();
            p.BeginOutputReadLine();
            p.WaitForExit();
            dispatcher.Invoke(() => resultHandler(output));           
        }
    }
}