using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace SeaTest
{
    /// <summary>
    /// </summary>
    public partial class SeaTestWindow : Window
    {
        public SeaTestViewModel Model { get; set; }
        public SeaTestWindow()
        {
            InitializeComponent();
            Model = new SeaTestViewModel();            
            DataContext = Model;
        }

        private void RunClick(object sender, RoutedEventArgs e)
        {
            Model.UpdateAndRun();
        }
    }
}
