using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace InstallBuilderLib
{
    public class PackageDescriptor
    {
        public string PackageName { get; set; }
        public string PackageDescription { get; set; }
        public Version PackageVersion { get; set; }
        public List<FileDescriptor> PackageFiles { get; set; }

        public PackageDescriptor(
            string packageName,
            string packageDescription,
            Version packageVersion)
        {
            PackageName = packageName;
            PackageVersion = packageVersion;
            PackageDescription = packageDescription;
            PackageFiles = new List<FileDescriptor>();
        }

        public static PackageDescriptor? FromFile(string file)
        {
            if (!File.Exists(file))
                throw new FileNotFoundException(string.Format("File {0} does not exist", file));

            string s = File.ReadAllText(file);
            PackageDescriptor? pd = JsonConvert.DeserializeObject<PackageDescriptor>(s);
            return pd;
        }

        public bool ToFile(string file)
        {
            try
            {
                string s = JsonConvert.SerializeObject(this);
                File.WriteAllText(file,s);
            } catch(Exception)
            {
                return false;
            }
            return true;
        }
    }
}
