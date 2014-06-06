#include "pch.h"

#include "SbsFile.h"

Sector SbsFile::sector() {
	return _root().child("MyObjectBuilder_Sector");
}