using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace InstallBuilderLib
{
    public class Version
    {
        [JsonProperty]
        public uint Major { get; set; }
        [JsonProperty]
        public uint Minor { get; set; }
        [JsonProperty]
        public uint BuildNumber { get; set; }

        public Version(uint major, uint minor, uint build)
        {
            Major = major;
            Minor = minor;
            BuildNumber = build;
        }

        public Version()
        {
            Major = 0;
            Minor = 0;
            BuildNumber = 0;
        }

        public static Version FromFile(string file)
        {
            Version? v = new Version();
            if (File.Exists(file))
            {
                string s = File.ReadAllText(file);
                v = JsonConvert.DeserializeObject<Version>(s);
                if (v == null)
                    return new Version();
            }
            return v;
        }

        public bool ToFile(string file)
        {
            try
            {
                string json = JsonConvert.SerializeObject(this);
                if (string.IsNullOrWhiteSpace(json))
                    return false;
                File.WriteAllText(file,json);
                return true;
            } catch(Exception)
            {
                return false;
            }
        }
    }
}
