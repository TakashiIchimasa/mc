T_b("/*---------------------------------------------------------------------");
T_b("\n");
T_b(" ");
T_b("* File:  ");
T_b(te_file->nvs);
T_b(".");
T_b(te_file->src_file_ext);
T_b("\n");
T_b(" ");
T_b("*");
T_b("\n");
T_b(" ");
T_b("* External Entity:  Non-Volatile Storage (NVS)");
T_b("\n");
T_b(" ");
T_b("*");
T_b("\n");
T_b(" ");
T_b("* Description:");
T_b("\n");
T_b(" ");
T_b("* Non-Volatile Storage (NVS) is used to persist class instances and");
T_b("\n");
T_b(" ");
T_b("* link instances for MC-3020 applications.");
T_b("\n");
T_b(" ");
T_b("*");
T_b("\n");
T_b(" ");
T_b("* item.length == 0 marks free space and is set by format and defrag.");
T_b("\n");
T_b(" ");
T_b("* item.length should only be zero for items past the end of the list");
T_b("\n");
T_b(" ");
T_b("* of items (otherwise the list is not traversable).");
T_b("\n");
T_b(" ");
T_b("* item.key == 0 && item.type == 0 means an entry has been deleted.");
T_b("\n");
T_b(" ");
T_b("*");
T_b("\n");
T_b(" ");
T_b("* NVS_search returns pointer to data.  (NVS_remove will back up to");
T_b("\n");
T_b(" ");
T_b("* mark an item as being deleted.)");
T_b("\n");
T_b(" ");
T_b("*");
T_b("\n");
T_b(" ");
T_b("* ");
T_b(te_copyright->body);
T_b("\n");
T_b(" ");
T_b("*-------------------------------------------------------------------*/");
T_b("\n");
T_b("#include <stdio.h>");
T_b("\n");
T_b("#include \"");
T_b(te_file->types);
T_b(".");
T_b(te_file->hdr_file_ext);
T_b("\"");
T_b("\n");
T_b("#include \"");
T_b(te_file->nvs);
T_b(".");
T_b(te_file->hdr_file_ext);
T_b("\"");
T_b("\n");
T_b("typedef struct {");
T_b("\n");
T_b("  ");
T_b("i_t length;");
T_b("\n");
T_b("  ");
T_b("u4_t key;");
T_b("\n");
T_b("  ");
T_b("c_t type;");
T_b("\n");
T_b("} NVS_item_t;");
T_b("\n");
T_b("#define NVS_ITEM_SIZE sizeof( NVS_item_t )");
T_b("\n");
T_b("#define NVS_MARK_DELETED      0x77");
T_b("\n");
T_b("#define NVS_file \"nvs.fil\"");
T_b("\n");
T_b("static NVS_item_t item;");
T_b("\n");
T_b("static i_t space_used;");
T_b("\n");
T_b("static i_t version = -999;");
T_b("\n");
T_b("FILE * store = 0;");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Search for a record matching the type and key or non-zero length.");
T_b("\n");
T_b(" ");
T_b("* Return length of record found, NOT_FOUND or ERROR.");
T_b("\n");
T_b(" ");
T_b("* Leave file pointer at instance data.");
T_b("\n");
T_b(" ");
T_b("* Leave item with meta data from found item.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("static i_t ");
T_b(te_prefix->result);
T_b("NVS_search( const u4_t, const i_t, c_t const *, const c_t );");
T_b("\n");
T_b("static i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_search(");
T_b("\n");
T_b("  ");
T_b("const u4_t key,");
T_b("\n");
T_b("  ");
T_b("const i_t length,");
T_b("\n");
T_b("  ");
T_b("c_t const * pointer,");
T_b("\n");
T_b("  ");
T_b("const c_t type )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result = 0;");
T_b("\n");
T_b("  ");
T_b("/*");
T_b("\n");
T_b("   ");
T_b("* Loop through looking for match.");
T_b("\n");
T_b("   ");
T_b("*/");
T_b("\n");
T_b("  ");
T_b("do {");
T_b("\n");
T_b("    ");
T_b("if ( fread( &item, NVS_ITEM_SIZE, 1u, store ) == 1 ) {");
T_b("\n");
T_b("      ");
T_b("if ( length != 0 ) { /* search on data */");
T_b("\n");
T_b("        ");
T_b("c_t buffer[ 64 ];");
T_b("\n");
T_b("        ");
T_b("i_t chunk = item.length;");
T_b("\n");
T_b("        ");
T_b("if ( chunk > sizeof( buffer ) ) {");
T_b("\n");
T_b("          ");
T_b("return NVS_ERROR_LENGTH;   /* Use better logic here.  */");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("        ");
T_b("if ( fread( buffer, chunk, 1u, store ) == 1 ) {");
T_b("\n");
T_b("          ");
T_b("if ( ( item->type == type ) && ( item->length == length ) ) {");
T_b("\n");
T_b("            ");
T_b("c_t const * p = pointer;");
T_b("\n");
T_b("            ");
T_b("c_t const * b = &buffer[ 0 ];");
T_b("\n");
T_b("            ");
T_b("result = item.length;  /* Assume match.  */");
T_b("\n");
T_b("            ");
T_b("while ( chunk-- > 0 ) {");
T_b("\n");
T_b("              ");
T_b("if ( *p++ != *b++ ) {");
T_b("\n");
T_b("                ");
T_b("result = 0;        /* not a match */");
T_b("\n");
T_b("                ");
T_b("/* Back track to beginning of data.  */");
T_b("\n");
T_b("                ");
T_b("if ( fseek( store, -item->length, SEEK_CUR ) != 0 ) {");
T_b("\n");
T_b("                  ");
T_b("result = NVS_ERROR_BAD_SEEK;");
T_b("\n");
T_b("                ");
T_b("}");
T_b("\n");
T_b("                ");
T_b("break;");
T_b("\n");
T_b("              ");
T_b("}");
T_b("\n");
T_b("            ");
T_b("}");
T_b("\n");
T_b("          ");
T_b("}");
T_b("\n");
T_b("        ");
T_b("} else {");
T_b("\n");
T_b("          ");
T_b("result = NVS_ERROR_BAD_READ;");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("} else if ( ( item->key == key ) && ( item->type == type ) ) {");
T_b("\n");
T_b("        ");
T_b("result = item.length;");
T_b("\n");
T_b("      ");
T_b("} else if ( item->length > 0 ) {");
T_b("\n");
T_b("        ");
T_b("/* Skip past data to next item.  */");
T_b("\n");
T_b("        ");
T_b("if ( fseek( store, item->length, SEEK_CUR ) != 0 ) {");
T_b("\n");
T_b("          ");
T_b("result = NVS_ERROR_BAD_SEEK;");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("} else {");
T_b("\n");
T_b("        ");
T_b("result = NVS_ERROR_NOT_FOUND;");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("    ");
T_b("} else {");
T_b("\n");
T_b("      ");
T_b("result = NVS_ERROR_BAD_READ;");
T_b("\n");
T_b("    ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("} while ( result == 0 );");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Search for a record NOT matching the key and type.");
T_b("\n");
T_b(" ");
T_b("* Return length of record found, NOT_FOUND or ERROR.");
T_b("\n");
T_b(" ");
T_b("* Leave file pointer at instance data.");
T_b("\n");
T_b(" ");
T_b("* Leave item with meta data from found item.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("static i_t ");
T_b(te_prefix->result);
T_b("NVS_nsearch( const u4_t, const c_t );");
T_b("\n");
T_b("static i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_nsearch(");
T_b("\n");
T_b("  ");
T_b("const u4_t key,");
T_b("\n");
T_b("  ");
T_b("const c_t type )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result = 0;");
T_b("\n");
T_b("  ");
T_b("/*");
T_b("\n");
T_b("   ");
T_b("* Loop through looking for match.");
T_b("\n");
T_b("   ");
T_b("*/");
T_b("\n");
T_b("  ");
T_b("do {");
T_b("\n");
T_b("    ");
T_b("if ( fread( &item, NVS_ITEM_SIZE, 1u, store ) == 1 ) {");
T_b("\n");
T_b("      ");
T_b("if ( ( item->key != key ) || ( item->type != type ) ) {");
T_b("\n");
T_b("        ");
T_b("result = item.length;");
T_b("\n");
T_b("      ");
T_b("} else if ( item->length > 0 ) {");
T_b("\n");
T_b("        ");
T_b("/* fseek will return non-zero on EOF or failure.  */");
T_b("\n");
T_b("        ");
T_b("result = fseek( store, item.length, SEEK_CUR );");
T_b("\n");
T_b("      ");
T_b("} else {");
T_b("\n");
T_b("        ");
T_b("result = NVS_ERROR_NOT_FOUND;");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("    ");
T_b("} else {");
T_b("\n");
T_b("      ");
T_b("result = NVS_ERROR_BAD_READ;");
T_b("\n");
T_b("    ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("} while ( result == 0 );");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  update");
T_b("\n");
T_b(" ");
T_b("* Update the record with changes.  The meta-data (key, length and type)");
T_b("\n");
T_b(" ");
T_b("* remain unchanged.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_update(");
T_b("\n");
T_b("  ");
T_b("u4_t ee_key,");
T_b("\n");
T_b("  ");
T_b("i_t ee_length,");
T_b("\n");
T_b("  ");
T_b("c_t const * ee_pointer,");
T_b("\n");
T_b("  ");
T_b("i_t ee_type )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result;");
T_b("\n");
T_b("  ");
T_b("if ( store != 0 ) {");
T_b("\n");
T_b("    ");
T_b("if ( ee_length <= NVS_MAX_ITEM_SIZE ) {");
T_b("\n");
T_b("      ");
T_b("if ( fseek( store, 0, SEEK_SET ) == 0 ) {");
T_b("\n");
T_b("        ");
T_b("c_t truncatedtype;");
T_b("\n");
T_b("        ");
T_b("truncatedtype = (c_t) ( ee_type && 0x00ff );");
T_b("\n");
T_b("        ");
T_b("/*");
T_b("\n");
T_b("         ");
T_b("* Search the store for the item.");
T_b("\n");
T_b("         ");
T_b("*/");
T_b("\n");
T_b("        ");
T_b("if ( ee_type == 0 ) { /* Search by data->  */");
T_b("\n");
T_b("          ");
T_b("result = ");
T_b(te_prefix->result);
T_b("NVS_search( 0, ee_length, ee_pointer, truncatedtype );");
T_b("\n");
T_b("        ");
T_b("} else {              /* Search by key and type.  */");
T_b("\n");
T_b("          ");
T_b("result = ");
T_b(te_prefix->result);
T_b("NVS_search( ee_key, 0, 0, truncatedtype );");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("        ");
T_b("if ( result == ee_length ) {");
T_b("\n");
T_b("          ");
T_b("if ( fseek( store, ftell(store), SEEK_SET ) == 0 ) {");
T_b("\n");
T_b("            ");
T_b("result = fwrite( ee_pointer, 1u, ee_length, store );");
T_b("\n");
T_b("            ");
T_b("if ( result != ee_length ) {");
T_b("\n");
T_b("              ");
T_b("result = NVS_ERROR_BAD_WRITE;");
T_b("\n");
T_b("            ");
T_b("}");
T_b("\n");
T_b("          ");
T_b("} else {");
T_b("\n");
T_b("            ");
T_b("result = NVS_ERROR_BAD_SEEK;");
T_b("\n");
T_b("          ");
T_b("}");
T_b("\n");
T_b("        ");
T_b("} else {");
T_b("\n");
T_b("          ");
T_b("/* Allow result from search to propogate.  */");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("} else {");
T_b("\n");
T_b("        ");
T_b("result = NVS_ERROR_BAD_SEEK;");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("    ");
T_b("} else {");
T_b("\n");
T_b("      ");
T_b("result = NVS_ERROR_ITEM_LONG;");
T_b("\n");
T_b("    ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("} else {");
T_b("\n");
T_b("    ");
T_b("result = NVS_ERROR_BAD_OPEN;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  insert");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_insert(");
T_b("\n");
T_b("  ");
T_b("u4_t ee_key,");
T_b("\n");
T_b("  ");
T_b("i_t ee_length,");
T_b("\n");
T_b("  ");
T_b("c_t const * ee_pointer,");
T_b("\n");
T_b("  ");
T_b("i_t ee_type )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result = NVS_RETURN_SUCCESS;");
T_b("\n");
T_b("  ");
T_b("if ( store != 0 ) {");
T_b("\n");
T_b("    ");
T_b("if ( ee_length <= NVS_MAX_ITEM_SIZE ) {");
T_b("\n");
T_b("      ");
T_b("if ( ee_length <= ");
T_b(te_prefix->result);
T_b("NVS_space_available() ) {");
T_b("\n");
T_b("        ");
T_b("result = ");
T_b(te_prefix->result);
T_b("NVS_update( ee_key, ee_length, ee_pointer, ee_type );");
T_b("\n");
T_b("        ");
T_b("if ( result <= 0 ) {");
T_b("\n");
T_b("          ");
T_b("if ( result == NVS_ERROR_NOT_FOUND ) {");
T_b("\n");
T_b("            ");
T_b("fseek( store, ftell( store ) - NVS_ITEM_SIZE, SEEK_SET );");
T_b("\n");
T_b("          ");
T_b("} else {");
T_b("\n");
T_b("            ");
T_b("fseek( store, 0, SEEK_END );");
T_b("\n");
T_b("          ");
T_b("}");
T_b("\n");
T_b("          ");
T_b("/*---------------------*/");
T_b("\n");
T_b("          ");
T_b("/* Load up the item.   */");
T_b("\n");
T_b("          ");
T_b("/*---------------------*/");
T_b("\n");
T_b("          ");
T_b("item.length = ee_length;");
T_b("\n");
T_b("          ");
T_b("item.key = ee_key;");
T_b("\n");
T_b("          ");
T_b("item.type = (c_t) ( ee_type && 0x00ff );");
T_b("\n");
T_b("          ");
T_b("result = fwrite( &item, NVS_ITEM_SIZE, 1u, store );");
T_b("\n");
T_b("          ");
T_b("if ( result == 1 ) {");
T_b("\n");
T_b("            ");
T_b("result = fwrite( ee_pointer, 1u, ee_length, store );");
T_b("\n");
T_b("            ");
T_b("if ( result == ee_length ) {");
T_b("\n");
T_b("              ");
T_b("space_used = space_used + NVS_ITEM_SIZE + ee_length;");
T_b("\n");
T_b("            ");
T_b("} else {");
T_b("\n");
T_b("              ");
T_b("result = NVS_ERROR_BAD_WRITE;");
T_b("\n");
T_b("            ");
T_b("}");
T_b("\n");
T_b("          ");
T_b("} else {");
T_b("\n");
T_b("            ");
T_b("result = NVS_ERROR_BAD_WRITE;");
T_b("\n");
T_b("          ");
T_b("}");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("} else {");
T_b("\n");
T_b("        ");
T_b("result = NVS_ERROR_NO_ROOM;");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("    ");
T_b("} else {");
T_b("\n");
T_b("      ");
T_b("result = NVS_ERROR_ITEM_LONG;");
T_b("\n");
T_b("    ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("} else {");
T_b("\n");
T_b("    ");
T_b("result = NVS_ERROR_BAD_OPEN;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  select");
T_b("\n");
T_b(" ");
T_b("* Input the expected length of the item.  This defines the space in");
T_b("\n");
T_b(" ");
T_b("* the calling buffer for writing the data.");
T_b("\n");
T_b(" ");
T_b("* Return the length of the selected item.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_select(");
T_b("\n");
T_b("  ");
T_b("u4_t ee_key,");
T_b("\n");
T_b("  ");
T_b("i_t ee_length,");
T_b("\n");
T_b("  ");
T_b("c_t * ee_pointer,");
T_b("\n");
T_b("  ");
T_b("i_t ee_type )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result = NVS_ERROR_NOT_FOUND;");
T_b("\n");
T_b("  ");
T_b("if ( store != 0 ) {");
T_b("\n");
T_b("    ");
T_b("/*-------------------------------------*/");
T_b("\n");
T_b("    ");
T_b("/* Go to beginning of file.            */");
T_b("\n");
T_b("    ");
T_b("/*-------------------------------------*/");
T_b("\n");
T_b("    ");
T_b("if ( fseek( store, 0, SEEK_SET ) == 0 ) {");
T_b("\n");
T_b("      ");
T_b("/*---------------------------------*/");
T_b("\n");
T_b("      ");
T_b("/* Search the store for the item.  */");
T_b("\n");
T_b("      ");
T_b("/*---------------------------------*/");
T_b("\n");
T_b("      ");
T_b("result = ");
T_b(te_prefix->result);
T_b("NVS_search( ee_key, 0, 0, ee_type );");
T_b("\n");
T_b("      ");
T_b("if ( result > 0 ) {");
T_b("\n");
T_b("        ");
T_b("if ( result <= ee_length ) {");
T_b("\n");
T_b("          ");
T_b("if ( fread( ee_pointer, 1u, result, store ) != result ) {");
T_b("\n");
T_b("            ");
T_b("result = NVS_ERROR_BAD_READ;");
T_b("\n");
T_b("          ");
T_b("}");
T_b("\n");
T_b("        ");
T_b("} else {");
T_b("\n");
T_b("          ");
T_b("result = NVS_ERROR_ITEM_LONG;");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("    ");
T_b("} else {");
T_b("\n");
T_b("      ");
T_b("result = NVS_ERROR_BAD_SEEK;");
T_b("\n");
T_b("    ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("} else {");
T_b("\n");
T_b("    ");
T_b("result = NVS_ERROR_BAD_OPEN;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  remove ");
T_b("\n");
T_b(" ");
T_b("* Return NVS_RETURN_SUCCESS when record deleted.");
T_b("\n");
T_b(" ");
T_b("* Return NVS_RETURN_NOT_FOUND when no record found to be deleted.");
T_b("\n");
T_b(" ");
T_b("* If data is given, search based on type and data, else type and key.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_remove(");
T_b("\n");
T_b("  ");
T_b("u4_t ee_key,");
T_b("\n");
T_b("  ");
T_b("i_t ee_length,");
T_b("\n");
T_b("  ");
T_b("c_t const * ee_pointer,");
T_b("\n");
T_b("  ");
T_b("i_t ee_type )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result = NVS_ERROR_NOT_FOUND;");
T_b("\n");
T_b("  ");
T_b("if ( store != 0 ) {");
T_b("\n");
T_b("    ");
T_b("/*");
T_b("\n");
T_b("     ");
T_b("* Go to beginning of file.");
T_b("\n");
T_b("     ");
T_b("*/");
T_b("\n");
T_b("    ");
T_b("if ( fseek( store, 0, SEEK_SET ) == 0 ) {");
T_b("\n");
T_b("      ");
T_b("c_t truncatedtype;");
T_b("\n");
T_b("      ");
T_b("truncatedtype = (c_t) ( ee_type && 0x00ff );");
T_b("\n");
T_b("      ");
T_b("/*");
T_b("\n");
T_b("       ");
T_b("* Search the store for the item.");
T_b("\n");
T_b("       ");
T_b("*/");
T_b("\n");
T_b("      ");
T_b("if ( ee_length != 0 ) { /* Search by type && data->  */");
T_b("\n");
T_b("        ");
T_b("result = ");
T_b(te_prefix->result);
T_b("NVS_search( 0, ee_length, ee_pointer, truncatedtype );");
T_b("\n");
T_b("      ");
T_b("} else {               /* Search by key and type.  */");
T_b("\n");
T_b("        ");
T_b("result = ");
T_b(te_prefix->result);
T_b("NVS_search( ee_key, 0, 0, truncatedtype );");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("if ( result > 0 ) {");
T_b("\n");
T_b("        ");
T_b("result = NVS_RETURN_SUCCESS;");
T_b("\n");
T_b("        ");
T_b("item.key = NVS_MARK_DELETED;");
T_b("\n");
T_b("        ");
T_b("item.type = NVS_MARK_DELETED;");
T_b("\n");
T_b("        ");
T_b("if ( fseek( store, 0 - NVS_ITEM_SIZE, SEEK_CUR ) == 0 ) {");
T_b("\n");
T_b("          ");
T_b("if ( fwrite( &item, NVS_ITEM_SIZE, 1u, store ) == 1 ) {");
T_b("\n");
T_b("            ");
T_b("space_used = space_used - item.length - NVS_ITEM_SIZE;");
T_b("\n");
T_b("          ");
T_b("} else {");
T_b("\n");
T_b("            ");
T_b("result = NVS_ERROR_BAD_WRITE;");
T_b("\n");
T_b("          ");
T_b("}");
T_b("\n");
T_b("        ");
T_b("} else {");
T_b("\n");
T_b("          ");
T_b("result = NVS_ERROR_BAD_SEEK;");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("    ");
T_b("} else {");
T_b("\n");
T_b("      ");
T_b("result = NVS_ERROR_BAD_SEEK;");
T_b("\n");
T_b("    ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("} else {");
T_b("\n");
T_b("    ");
T_b("result = NVS_ERROR_BAD_OPEN;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  space_available");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_space_available( void )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("return NVS_STORAGE_SIZE - space_used - NVS_ITEM_SIZE;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  space_used");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_space_used( void )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("return space_used;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  space_total");
T_b("\n");
T_b(" ");
T_b("* Return the size of the non-volatile storage (NVS).");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_space_total( void )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("return NVS_STORAGE_SIZE;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  initialize");
T_b("\n");
T_b(" ");
T_b("* Set up the internal data structures (and file pointers).");
T_b("\n");
T_b(" ");
T_b("* Return NVS_RETURN_SUCCESS or error.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_initialize( void )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result = NVS_RETURN_SUCCESS;");
T_b("\n");
T_b("  ");
T_b("c_t done = 0;");
T_b("\n");
T_b("  ");
T_b("space_used = 0;");
T_b("\n");
T_b("  ");
T_b("/*-------------------------------------------------------*/");
T_b("\n");
T_b("  ");
T_b("/* Close file.                                           */");
T_b("\n");
T_b("  ");
T_b("/* Open the file for random access reading and writing.  */");
T_b("\n");
T_b("  ");
T_b("/*-------------------------------------------------------*/");
T_b("\n");
T_b("  ");
T_b("if ( store != 0 ) { fclose( store ); }");
T_b("\n");
T_b("  ");
T_b("store = fopen( NVS_file, \"rb+\" );");
T_b("\n");
T_b("  ");
T_b("if ( store != 0 ) {");
T_b("\n");
T_b("    ");
T_b("do {");
T_b("\n");
T_b("      ");
T_b("if ( fread( &item, NVS_ITEM_SIZE, 1u, store ) == 1 ) {");
T_b("\n");
T_b("        ");
T_b("if ( item->length > 0 ) {");
T_b("\n");
T_b("          ");
T_b("space_used = space_used + item.length + NVS_ITEM_SIZE,");
T_b("\n");
T_b("          ");
T_b("done = fseek( store, item.length, SEEK_CUR );");
T_b("\n");
T_b("        ");
T_b("} else {");
T_b("\n");
T_b("          ");
T_b("done = 1;");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("} else {");
T_b("\n");
T_b("        ");
T_b("done = 1;");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("    ");
T_b("} while ( done == 0 );");
T_b("\n");
T_b("    ");
T_b("fseek( store, 0, SEEK_SET );");
T_b("\n");
T_b("  ");
T_b("} else {");
T_b("\n");
T_b("    ");
T_b("result = NVS_ERROR_BAD_OPEN;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  format");
T_b("\n");
T_b(" ");
T_b("* Return NVS_RETURN_SUCCESS or error.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_format( void )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result = NVS_RETURN_SUCCESS;");
T_b("\n");
T_b("  ");
T_b("/*-------------------------------------------------------*/");
T_b("\n");
T_b("  ");
T_b("/* Create the file discarding any previous data.         */");
T_b("\n");
T_b("  ");
T_b("/*-------------------------------------------------------*/");
T_b("\n");
T_b("  ");
T_b("if ( store != 0 ) { fclose( store ); }");
T_b("\n");
T_b("  ");
T_b("store = fopen( NVS_file, \"wb+\" );");
T_b("\n");
T_b("  ");
T_b("if ( store != 0 ) {");
T_b("\n");
T_b("    ");
T_b("fclose( store );");
T_b("\n");
T_b("    ");
T_b("result = ");
T_b(te_prefix->result);
T_b("NVS_initialize();");
T_b("\n");
T_b("  ");
T_b("} else {");
T_b("\n");
T_b("    ");
T_b("result = NVS_ERROR_BAD_OPEN;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Copy from one place in a file to another.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("static i_t ");
T_b(te_prefix->result);
T_b("NVS_copy( i_t, i_t, i_t );");
T_b("\n");
T_b("static i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_copy(");
T_b("\n");
T_b("  ");
T_b("i_t dest,");
T_b("\n");
T_b("  ");
T_b("i_t src,");
T_b("\n");
T_b("  ");
T_b("i_t length )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("c_t buffer[ 64 ];");
T_b("\n");
T_b("  ");
T_b("i_t chunk, remaining = length;");
T_b("\n");
T_b("  ");
T_b("while ( remaining > 0 ) {");
T_b("\n");
T_b("    ");
T_b("chunk = ( remaining > sizeof( buffer ) ) ? sizeof( buffer ) : remaining;");
T_b("\n");
T_b("    ");
T_b("if ( fseek( store, src, SEEK_SET ) == 0 ) {");
T_b("\n");
T_b("      ");
T_b("if ( fread( buffer, 1u, chunk, store ) == chunk ) {");
T_b("\n");
T_b("        ");
T_b("src = ftell( store );");
T_b("\n");
T_b("        ");
T_b("if ( fseek( store, dest, SEEK_SET ) == 0 ) {");
T_b("\n");
T_b("          ");
T_b("if ( fwrite( buffer, 1u, chunk, store ) > 0 ) {");
T_b("\n");
T_b("            ");
T_b("remaining = remaining - chunk;");
T_b("\n");
T_b("            ");
T_b("dest = ftell( store );");
T_b("\n");
T_b("          ");
T_b("} else {");
T_b("\n");
T_b("            ");
T_b("remaining = NVS_ERROR_BAD_WRITE;");
T_b("\n");
T_b("          ");
T_b("}");
T_b("\n");
T_b("        ");
T_b("} else {");
T_b("\n");
T_b("          ");
T_b("remaining = NVS_ERROR_BAD_SEEK;");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("} else {");
T_b("\n");
T_b("        ");
T_b("remaining = NVS_ERROR_BAD_READ;");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("    ");
T_b("} else {");
T_b("\n");
T_b("      ");
T_b("remaining = NVS_ERROR_BAD_SEEK;");
T_b("\n");
T_b("    ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("return remaining;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  defrag");
T_b("\n");
T_b(" ");
T_b("* - Find a deleted item.");
T_b("\n");
T_b(" ");
T_b("* - Search ahead for a non-deleted item.");
T_b("\n");
T_b(" ");
T_b("* - Move non-deleted item down over deleted item.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_defrag( void )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result = NVS_RETURN_SUCCESS;");
T_b("\n");
T_b("  ");
T_b("i_t contiguous, middle, scan;");
T_b("\n");
T_b("  ");
T_b("/*-------------------------------------*/");
T_b("\n");
T_b("  ");
T_b("/* Go to beginning of file.            */");
T_b("\n");
T_b("  ");
T_b("/*-------------------------------------*/");
T_b("\n");
T_b("  ");
T_b("if ( fseek( store, 0, SEEK_SET ) == 0 ) {");
T_b("\n");
T_b("    ");
T_b("/*---------------------------------------*/");
T_b("\n");
T_b("    ");
T_b("/* Search the store for a deleted item.  */");
T_b("\n");
T_b("    ");
T_b("/*---------------------------------------*/");
T_b("\n");
T_b("    ");
T_b("if ( ");
T_b(te_prefix->result);
T_b("NVS_search( NVS_MARK_DELETED, 0, 0, NVS_MARK_DELETED ) > 0 ) {");
T_b("\n");
T_b("      ");
T_b("contiguous = ftell( store ) - NVS_ITEM_SIZE;");
T_b("\n");
T_b("      ");
T_b("if ( item->length > 0 ) {");
T_b("\n");
T_b("        ");
T_b("/* Skip up past instance data.  */");
T_b("\n");
T_b("        ");
T_b("fseek( store, item.length, SEEK_CUR );");
T_b("\n");
T_b("      ");
T_b("} else {");
T_b("\n");
T_b("        ");
T_b("return 1;");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("while ( result == 0 ) {");
T_b("\n");
T_b("        ");
T_b("if ( ");
T_b(te_prefix->result);
T_b("NVS_nsearch( NVS_MARK_DELETED, NVS_MARK_DELETED ) > 0 ) {");
T_b("\n");
T_b("          ");
T_b("middle = ftell( store ) - NVS_ITEM_SIZE;");
T_b("\n");
T_b("          ");
T_b("scan = middle + item.length + NVS_ITEM_SIZE;");
T_b("\n");
T_b("          ");
T_b("if ( ( result =");
T_b("\n");
T_b("            ");
T_b(te_prefix->result);
T_b("NVS_copy( contiguous, middle, item.length + NVS_ITEM_SIZE ) )");
T_b("\n");
T_b("            ");
T_b("< 0 ) {");
T_b("\n");
T_b("            ");
T_b("break;");
T_b("\n");
T_b("          ");
T_b("}");
T_b("\n");
T_b("          ");
T_b("contiguous = contiguous + NVS_ITEM_SIZE + item.length;");
T_b("\n");
T_b("          ");
T_b("fseek( store, scan, SEEK_SET );");
T_b("\n");
T_b("        ");
T_b("} else {");
T_b("\n");
T_b("          ");
T_b("/* No more useful items after, so mark end of data.  */");
T_b("\n");
T_b("          ");
T_b("fseek( store, contiguous, SEEK_SET );");
T_b("\n");
T_b("          ");
T_b("item.key = NVS_MARK_DELETED;");
T_b("\n");
T_b("          ");
T_b("item.type = NVS_MARK_DELETED;");
T_b("\n");
T_b("          ");
T_b("item.length = 0;");
T_b("\n");
T_b("          ");
T_b("fwrite( &item, NVS_ITEM_SIZE, 1u, store );");
T_b("\n");
T_b("          ");
T_b("break;");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("    ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("} else {");
T_b("\n");
T_b("    ");
T_b("result = NVS_ERROR_BAD_SEEK;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  next");
T_b("\n");
T_b(" ");
T_b("* The input ee_length gives the storage available for copying in");
T_b("\n");
T_b(" ");
T_b("* a record of data.");
T_b("\n");
T_b(" ");
T_b("* Return the length of the record returned.");
T_b("\n");
T_b(" ");
T_b("* Write the data into the input pointer.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_next(");
T_b("\n");
T_b("  ");
T_b("u4_t * ee_key,");
T_b("\n");
T_b("  ");
T_b("i_t ee_length,");
T_b("\n");
T_b("  ");
T_b("c_t * ee_pointer,");
T_b("\n");
T_b("  ");
T_b("i_t * ee_type )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result = NVS_RETURN_SUCCESS;");
T_b("\n");
T_b("  ");
T_b("if ( store != 0 ) {");
T_b("\n");
T_b("    ");
T_b("if ( fread( &item, NVS_ITEM_SIZE, 1u, store ) == 1 ) {");
T_b("\n");
T_b("      ");
T_b("if ( item->length <= ee_length ) {");
T_b("\n");
T_b("        ");
T_b("if ( fread( ee_pointer, 1u, item->length, store ) == item->length ) {");
T_b("\n");
T_b("          ");
T_b("result = item.length;");
T_b("\n");
T_b("          ");
T_b("*ee_key = item.key;");
T_b("\n");
T_b("          ");
T_b("*ee_type = item.type;");
T_b("\n");
T_b("        ");
T_b("} else {");
T_b("\n");
T_b("          ");
T_b("result = NVS_ERROR_BAD_READ;");
T_b("\n");
T_b("        ");
T_b("}");
T_b("\n");
T_b("      ");
T_b("} else {");
T_b("\n");
T_b("        ");
T_b("result = NVS_ERROR_ITEM_LONG;");
T_b("\n");
T_b("      ");
T_b("}");
T_b("\n");
T_b("    ");
T_b("} else {");
T_b("\n");
T_b("      ");
T_b("result = NVS_ERROR_BAD_READ;");
T_b("\n");
T_b("    ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("} else {");
T_b("\n");
T_b("    ");
T_b("result = NVS_ERROR_BAD_OPEN;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  checksum");
T_b("\n");
T_b(" ");
T_b("* Calculate a checksum on the data in the non-volatile store (NVS).");
T_b("\n");
T_b(" ");
T_b("* Return zero when happy.");
T_b("\n");
T_b(" ");
T_b("*");
T_b("\n");
T_b(" ");
T_b("* Note:  This is not implemented by MC-3020.");
T_b("\n");
T_b(" ");
T_b("*        Customer/User must supply this capability.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_checksum(");
T_b("\n");
T_b("  ");
T_b("i_t ee_first,");
T_b("\n");
T_b("  ");
T_b("i_t ee_second )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("i_t result = -1;   /* Fail, since we have no code.  */");
T_b("\n");
T_b("  ");
T_b("return result;");
T_b("\n");
T_b("}");
T_b("\n");
T_b("/*");
T_b("\n");
T_b(" ");
T_b("* Bridge:  version");
T_b("\n");
T_b(" ");
T_b("* Return a version that can be used by the application.");
T_b("\n");
T_b(" ");
T_b("* An argument is supplied so that a version may also be written");
T_b("\n");
T_b(" ");
T_b("* if desired->");
T_b("\n");
T_b(" ");
T_b("* Return the version as an integer.");
T_b("\n");
T_b(" ");
T_b("*");
T_b("\n");
T_b(" ");
T_b("* Note:  This is not implemented by MC-3020.");
T_b("\n");
T_b(" ");
T_b("*        Customer/User must supply this capability.");
T_b("\n");
T_b(" ");
T_b("*/");
T_b("\n");
T_b("i_t");
T_b("\n");
T_b(te_prefix->result);
T_b("NVS_version(");
T_b("\n");
T_b("  ");
T_b("i_t ee_first,");
T_b("\n");
T_b("  ");
T_b("i_t ee_second )");
T_b("\n");
T_b("{");
T_b("\n");
T_b("  ");
T_b("if ( ee_first == 1 ) {");
T_b("\n");
T_b("    ");
T_b("version = ee_second;");
T_b("\n");
T_b("  ");
T_b("}");
T_b("\n");
T_b("  ");
T_b("return version;");
T_b("\n");
T_b("}");
T_b("\n");
