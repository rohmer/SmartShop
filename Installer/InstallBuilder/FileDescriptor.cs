using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace InstallBuilderLib
{
    public enum eFileType
    {
        SYSTEM=0,
        UI=1,
        DEVICE=2
    }

    [JsonObject(MemberSerialization.OptIn)]
    public class FileDescriptor
    {
        [JsonProperty]
        public string SourceFile { get; set; }

        [JsonProperty]
        public string DestinationFolder { get; set; }

        [JsonProperty]
        public string MD5Hash { get; private set; }

        [JsonProperty]
        public eFileType FileType { get; set; }

        [JsonProperty]
        public Version FileVersion { get; set; }

        public FileDescriptor(string sourceFile, 
            string destFolder,
            eFileType fileType,
            Version fileVersion)
        {
            SourceFile = sourceFile;
            DestinationFolder = destFolder;
            FileType = fileType;
            FileVersion = fileVersion;
            MD5Hash = string.Empty;
        }

        public void GenerateHash()
        {
            MD5Hash = Utilities.GenerateFileMD5(SourceFile);
        }
    }
}
