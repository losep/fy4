 // medicine.c
inherit ITEM;
#include <ansi.h> 
void create()
{
    set_name(RED"�Ż���¶��"NOR,({"yulu wan","wan"}));
        set_weight(60);
        if( clonep() )
                set_default_object(__FILE__);
        else {
            set("long",
                "��˵��ҩ���ǲɼ�ÿ�ճ���ʱ�����ʻ������ϵ�¶ˮ���ƶ��ɣ�������\nɫ������Ϯ�ˣ��������񣬹�Ч��������\n");
            set("unit","��");
        set("value", 100000);
        }
        ::init_item();
} 
void init()
{
  if(this_player()==environment())
        add_action("apply_medicine","yong");
} 
int apply_medicine()
{
        int value = 20;
        int diff; 
        if(this_player()->is_fighting())
            return notify_fail("ս���в�����ҩ����\n");
        diff = this_player()->query("max_gin")-this_player()->query("eff_gin");
        if(!(diff))    return notify_fail("��û�����ˣ�\n");
    if(value < diff) value = diff;
            
    message_vision("$NС����������һ�žŻ���¶�裬������ˬ�ޱȣ�����Ȼһ��\n",this_player());
        this_player()->add("eff_gin",value);
        destruct(this_object());
        return 1;
}    