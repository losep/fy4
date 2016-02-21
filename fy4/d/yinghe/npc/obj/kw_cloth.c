 // -neon
#include <ansi.h>
#include <armor.h>
inherit CLOTH;
void create()
{
    set_name(HIW"白裘劲装"NOR, ({ "white cloth", "cloth" }) );
    set_weight(4000);
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "件");
        set("long", "一件白色的用皮裘做的劲装，分外的轻柔保暖。\n");
        set("material", "cloth");
        set("bigcloth", 1);
        set("armor_prop/armor", 30);
        set("value",4000);
    }
    ::init_cloth();
}   
