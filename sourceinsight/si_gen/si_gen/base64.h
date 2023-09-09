
#pragma once

#include "pch.h"
#include "framework.h"


void base64_encode(const unsigned char* src, int srclen, unsigned char* dest, int destlen);
void base64_decode(const unsigned char* src, size_t srclen, unsigned char* dest, size_t destlen);
