#include <ansi.h>
#include <armor.h>
inherit ARMOR;
void create()
{
        set_name(HIW"������"NOR, ({ "silver chainarmor","chainarmor" }) );
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "silver");
                set("long", "һ����������İ������ס�\n");
                set("value", 20000);
                set("armor_prop/armor", 60);
        }
        ::init_armor();
} 