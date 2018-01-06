using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS_Adapter
{
    /// <summary>
    /// All data of the file on disk
    /// </summary>
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class DirEntry
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string fileName;
        public string FileName { get { return fileName; } }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        string fileOwner;
        public string FileOwner { get { return fileOwner; } }
        uint fileAddr;
        public uint FileAddr { get { return fileAddr; } }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        string crDate;
        public string CrDate { get { return crDate; } }
        uint fileSize;
        public uint FileSize { get { return fileSize; } }
        uint eofRecNr;
        public uint EofRecNr { get { return eofRecNr; } }
        uint maxRecSize;
        public uint MaxRecSize { get { return maxRecSize; } }
        uint actualRecSize;
        public uint ActualRecSize { get { return actualRecSize; } }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 2)]
        string recFormat;
        public string RecFormat { get { return recFormat; } }
        uint keyOffset;
        public uint KeyOffset { get { return keyOffset; } }
        uint keySize;
        public uint KeySize { get { return keySize; } }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 2)]
        string keyType;
        public string KeyType { get { return keyType; } }
        char entryStatus;
        public char EntryStatus { get { return entryStatus; } }
    }
}
