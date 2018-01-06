using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS_Adapter
{
    public class FCB
    {
        private IntPtr myFCBpointer;
        /// <name>
        /// constractor with out parameters
        /// </name>
        /// <summary>
        /// constractor with out parameters-Update fields of FCB
        /// </summary>
        public FCB(IntPtr myFCBpointer)
        {
            this.myFCBpointer = myFCBpointer;
        }
        /// <name>
        /// destractor with out parameters
        /// </name>
        /// <summary>
        /// destractor with out parameters-The role of this function to destroy an object of this type automatically at the appropriate moment.
        /// </summary>
        ~FCB()
        {
            if (myFCBpointer != null)
                cppToCsharpAdapter.deleteFcbObject(ref myFCBpointer);
        }
        /// <name>
        /// closefile-0 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to close the particular file
        /// </summary>
        public void Closefile()
        {
            try
            {
                cppToCsharpAdapter.closefile(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        /// <name>
        /// readrec-2 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to read the current record of the file
        /// </summary>
        /// <param name="record">Current record</param>
        /// <param name="readForUpdate">Whether the file is opened as read for update</param>
        public object readRec(object dest, bool readForUpdate = false)
        {
            try
            {

                IntPtr buffer;
                buffer = Marshal.AllocHGlobal(Marshal.SizeOf(dest.GetType()));

                cppToCsharpAdapter.readRec(this.myFCBpointer, buffer, readForUpdate);
                Marshal.PtrToStructure(buffer, dest);

                Marshal.FreeHGlobal(buffer);

                return dest;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        /// <name>
        /// writerec-1 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to write the record first parameter passed into the current position of the file
        /// </summary>
        /// <param name="record">Current record</param>
        public void writeRec(object source)
        {
            try
            {
                IntPtr buffer = Marshal.AllocHGlobal(Marshal.SizeOf(source.GetType()));
                Marshal.StructureToPtr(source, buffer, true);

                cppToCsharpAdapter.writeRec(this.myFCBpointer, buffer);

                Marshal.FreeHGlobal(buffer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        /// <name>
        /// seekrec-2 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to read the current record of the file
        /// </summary>
        /// <param name="SearchType">Search type (0 - beginning of file, 1 - from the current record, 2 - the end of the logical file)</param>
        /// <param name="JumpNr">Some records the user wants to "jump" forward or backward</param>
        public void seekRec(uint from, int pos)
        {
            try
            {
                cppToCsharpAdapter.seekRec(this.myFCBpointer, from, pos);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        /// <name>
        /// updateCancel-0 parameters
        /// </name>
        /// <summary>
        /// The role of this function to cancel the lock status of the current record
        /// </summary>
        public void updateRecCancel()
        {
            try
            {
                cppToCsharpAdapter.updateRecCancel(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        /// <name>
        /// deleteRec-0 parameters
        /// </name>
        /// <summary>
        /// The role of this function to delete a record instead of the current file
        /// </summary>
        public void deleteRec()
        {
            try
            {
                cppToCsharpAdapter.deleteRec(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        /// <name>
        /// updateRec-1 parameters
        /// </name>
        /// <summary>
        /// The role of this function is to write a record instead of the current file, to update
        /// </summary>
        /// <param name="record">Current record</param>
        public void updateRec(object source)
        {
            try
            {
                IntPtr buffer = Marshal.AllocHGlobal(Marshal.SizeOf(source.GetType()));
                Marshal.StructureToPtr(source, buffer, true);
                cppToCsharpAdapter.updateRec(this.myFCBpointer, buffer);
                Marshal.FreeHGlobal(buffer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
    }
}
