using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public class CaesarStream : Stream
    {
        private readonly Stream _innerStream;
        private readonly int _shift;

        public CaesarStream(Stream innerStream, int shift)
        {
            _innerStream = innerStream ?? throw new ArgumentNullException(nameof(innerStream));
            _shift = shift;
        }

        public override bool CanRead => _innerStream.CanRead;
        public override bool CanSeek => _innerStream.CanSeek;
        public override bool CanWrite => _innerStream.CanWrite;
        public override long Length => _innerStream.Length;

        public override long Position
        {
            get => _innerStream.Position;
            set => _innerStream.Position = value;
        }

        public override void Flush()
        {
            _innerStream.Flush();
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            int read = _innerStream.Read(buffer, offset, count);
            for (int i = offset; i < offset + read; i++)
            {
                buffer[i] = (byte)((buffer[i] + _shift + 256) % 256); // zapewnia poprawne działanie przy ujemnych przesunięciach
            }
            return read;
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            byte[] encoded = new byte[count];
            for (int i = 0; i < count; i++)
            {
                encoded[i] = (byte)((buffer[offset + i] + _shift + 256) % 256);
            }
            _innerStream.Write(encoded, 0, count);
        }

        public override long Seek(long offset, SeekOrigin origin)
        {
            return _innerStream.Seek(offset, origin);
        }

        public override void SetLength(long value)
        {
            _innerStream.SetLength(value);
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                _innerStream.Dispose();
            }
            base.Dispose(disposing);
        }
    }

}
