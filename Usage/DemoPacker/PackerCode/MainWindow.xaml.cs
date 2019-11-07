using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Path = System.IO.Path;

namespace Packer
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        string path;
        string dirname;
        string filename;
        bool lv = false;
        delegate string GetSubString(string filename);

        public MainWindow()
        {
            InitializeComponent();
        }

        private void OkButton_Click(object sender, RoutedEventArgs e)
        {
            path = @"" + PathTextBox.Text;
            var fileNameArray = Directory.GetFiles(path);
            for(int i = 0; i < fileNameArray.Length; i++)
            {
                filename = Path.GetFileName(fileNameArray[i]);
                dirname = Path.GetFileNameWithoutExtension(fileNameArray[i]);
                DirectoryInfo directoryInfo = new DirectoryInfo(path + @"\" + dirname);
                if (!directoryInfo.Exists)
                    directoryInfo.Create();
                try
                {
                    File.Move(path + @"\" + filename, path + @"\" + dirname + @"\" + filename);
                    if(lv == false)
                    {
                        MessageBox.Show("Упаковка файла(-ов) прашла успешно");
                        lv = true;
                    }                    
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }                
            }
            this.Close();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
