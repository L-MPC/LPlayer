
#pragma once

namespace Utf8 { // could be a static class, instead of a namespace, if it needs private members
	// basic classification of UTF-8 bytes
	inline static bool isSingleByte(unsigned char c)       { return c < 0x80; }
	inline static bool isPartOfMultibyte(unsigned char c)  { return c >= 0x80; }
	inline static bool isFirstOfMultibyte(unsigned char c) { return c >= 0xC2 && c < 0xF5; } // 0xF5 to 0xFD are defined by UTF-8, but are not currently valid Unicode
	inline static bool isContinuation(unsigned char c)     { return (c & 0xC0) == 0x80; }
	inline static bool isValid(unsigned char c)            { return c < 0xC0 || isFirstOfMultibyte(c); }	// validates a byte, out of context

	// number of continuation bytes for a given valid first character (0 for single byte characters)
	inline static int  continuationBytes(unsigned char c)  {
		static const char _len[] = { 1,1,2,3 };
		return (c < 0xC0) ? 0 : _len[(c & 0x30) >>  4];
	} 

	// validates a full character
	inline static bool isValid(const unsigned char* buf, int buflen) {
		if(isSingleByte(buf[0])) return true; // single byte is valid
		if(!isFirstOfMultibyte(buf[0])) return false; // not single byte, nor valid multi-byte first byte
		int charContinuationBytes = continuationBytes(buf[0]);
		if(buflen < charContinuationBytes+1) return false; // character does not fit in buffer
		for(int i = charContinuationBytes; i>0; --i)
			if(!isContinuation(*(++buf))) return false; // not enough continuation bytes
		return true;  // the character is valid (if there are too many continuation bytes, it is the next character that will be invalid)
	}

	// rewinds to the first byte of a multi-byte character for any valid UTF-8 (and will not rewind too much on any other input)
	inline static int characterStart(const unsigned char* buf, int startingIndex) {
		int charContinuationBytes = 0;
		while(charContinuationBytes < startingIndex	// rewind past start of buffer?
			&& charContinuationBytes < 5	// UTF-8 support up to 5 continuation bytes (but valid sequences currently do not have more than 3)
			&& isContinuation(buf[startingIndex-charContinuationBytes])
			)
			++charContinuationBytes;
		return startingIndex-charContinuationBytes;
	}
};
