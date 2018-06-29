+// =========================================================================
+// Monk APL
+// =========================================================================
+
+// monk_t::default_flask ===================================================
+std::string monk_t::default_flask() const
+{
+  switch ( specialization() )
+  {
+    case MONK_BREWMASTER:
+      if ( true_level > 100)
+        return "seventh_demon";
+      else if ( true_level > 90 )
+        return "greater_draenic_agility_flask";
+      else if ( true_level > 85 )
+        return "spring_blossoms";
+      else if ( true_level > 80 )
+        return "winds";
+      else if ( true_level > 75 )
+        return "endless_rage";
+      else if ( true_level > 70 )
+        return "relentless_assault";
+      else
+        return "disabled";
+      break;
+    case MONK_MISTWEAVER:
+      if ( true_level > 100 )
+        return "whispered_pact";
+      else if ( true_level > 90 )
+        return "greater_draenic_intellect_flask";
+      else if ( true_level > 85 )
+        return "warm_sun";
+      else if ( true_level > 80 )
+        return "draconic_mind";
+      else if ( true_level > 70 )
+        return "blinding_light";
+      else
+        return "disabled";
+      break;
+    case MONK_WINDWALKER:
+      if ( true_level > 100 )
+        return "seventh_demon";
+      else if ( true_level > 90 )
+        return "greater_draenic_agility_flask";
+      else if ( true_level > 85 )
+        return "spring_blossoms";
+      else if ( true_level > 80 )
+        return "winds";
+      else if ( true_level > 75 )
+        return "endless_rage";
+      else if (true_level > 70)
+        return "relentless_assault";
+      else
+        return "disabled";
+      break;
+    default:
+      return "disabled";
+      break;
+  }
+}
+
+// monk_t::default_potion ==================================================
+std::string monk_t::default_potion() const
+{
+  switch ( specialization() )
+  {
+    case MONK_BREWMASTER:
+      if ( true_level > 100)
+        return "old_war";
+      else if ( true_level > 90 )
+        return "draenic_agility";
+      else if ( true_level > 85 )
+        return "virmens_bite";
+      else if ( true_level > 80 )
+        return "tolvir";
+      else if ( true_level > 70 )
+        return "wild_magic";
+      else if ( true_level > 60 )
+        return "haste";
+      else
+        return "disabled";
+      break;
+    case MONK_MISTWEAVER:
+      if ( true_level > 100 )
+        return "prolonged_power";
+      else if ( true_level > 90 )
+        return "draenic_intellect";
+      else if ( true_level > 85 )
+        return "jade_serpent";
+      else if ( true_level > 80 )
+        return "volcanic";
+      else if ( true_level > 70 )
+        return "wild_magic";
+      else if ( true_level > 60 )
+        return "destruction";
+      else
+        return "disabled";
+      break;
+    case MONK_WINDWALKER:
+      if ( true_level > 100 )
+        return "prolonged_power";
+      else if ( true_level > 90 )
+        return "draenic_agility";
+      else if ( true_level > 85 )
+        return "virmens_bite";
+      else if ( true_level > 80 )
+        return "tolvir";
+      else if ( true_level > 70 )
+        return "wild_magic";
+      else if (true_level > 60 )
+        return "haste";
+      else
+        return "disabled";
+      break;
+    default:
+      return "disabled";
+      break;
+  }
+}
+
+// monk_t::default_food ====================================================
+std::string monk_t::default_food() const
+{  switch ( specialization() )
+  {
+    case MONK_BREWMASTER:
+      if ( true_level > 100)
+        return "fishbrul_special";
+      else if ( true_level > 90 )
+        return "salty_squid_roll";
+      else if ( true_level > 85 )
+        return "sea_mist_rice_noodles";
+      else if ( true_level > 80 )
+        return "skewered_eel";
+      else if ( true_level > 70 )
+        return "blackened_dragonfin";
+      else if ( true_level > 60 )
+        return "warp_burger";
+      else
+        return "disabled";
+      break;
+    case MONK_MISTWEAVER:
+      if ( true_level > 100 )
+        return "lavish_suramar_feast";
+      else if ( true_level > 90 )
+        return "salty_squid_roll";
+      else if ( true_level > 85 )
+        return "sea_mist_rice_noodles";
+      else if ( true_level > 80 )
+        return "skewered_eel";
+      else if ( true_level > 70 )
+        return "blackened_dragonfin";
+      else if ( true_level > 60 )
+        return "warp_burger";
+      else
+        return "disabled";
+      break;
+    case MONK_WINDWALKER:
+      if ( true_level > 100 )
+        return "lavish_suramar_feast";
+      else if ( true_level > 90 )
+        return "salty_squid_roll";
+      else if ( true_level > 85 )
+        return "sea_mist_rice_noodles";
+      else if ( true_level > 80 )
+        return "skewered_eel";
+      else if ( true_level > 70 )
+        return "blackened_dragonfin";
+      else if (true_level > 60 )
+        return "warp_burger";
+      else
+        return "disabled";
+      break;
+    default:
+      return "disabled";
+      break;
+  }
+}
+
+// monk_t::default_rune ====================================================
+std::string monk_t::default_rune() const
+{
+  return (true_level >= 110) ? "defiled" :
+    (true_level >= 100) ? "hyper" :
+    "disabled";
+}
+
+// Windwalker Combat Action Priority List ===============================
+
+void monk_t::apl_combat_windwalker() {
+  std::vector<std::string> racial_actions = get_racial_actions();
+  action_priority_list_t* def = get_action_priority_list( "default" );
+  action_priority_list_t* cd = get_action_priority_list( "cd" );
+  action_priority_list_t* sef = get_action_priority_list( "sef" );
+  action_priority_list_t* sef_opener = get_action_priority_list( "sef_opener" );
+  action_priority_list_t* serenity = get_action_priority_list( "serenity" );
+  action_priority_list_t* serenity_opener = get_action_priority_list( "serenity_opener" );
+  action_priority_list_t* aoe = get_action_priority_list( "aoe" );
+  action_priority_list_t* st = get_action_priority_list( "st" );
+
+  def -> add_action( "auto_attack" );
+  def -> add_action( this, "Spear Hand Strike", "if=target.debuff.casting.react" );
+  def -> add_action( this, "Touch of Karma", "interval=90,pct_health=0.5", "Touch of Karma on cooldown, if Good Karma is enabled equal to 100% of maximum health" );
+  def -> add_action( this, "Touch of Karma", "interval=90,pct_health=1.0" );
+
+  if ( sim -> allow_potions )
+  {
+    if ( true_level >= 100 )
+      def -> add_action( "potion,if=buff.serenity.up|buff.storm_earth_and_fire.up|(!talent.serenity.enabled&trinket.proc.agility.react)|buff.bloodlust.react|target.time_to_die<=60",
+                            "Potion if Serenity or Storm, Earth, and Fire are up or you are running serenity and a main stat trinket procs, or you are under the effect of bloodlust, or target time to die is greater or equal to 60" );
+    else
+      def -> add_action( "potion,if=buff.storm_earth_and_fire.up|trinket.proc.agility.react|buff.bloodlust.react|target.time_to_die<=60" );
+  }
+
+  def -> add_action( this, "Touch of Death", "if=target.time_to_die<=9" );
+  def -> add_action( "call_action_list,name=serenity,if=(talent.serenity.enabled&cooldown.serenity.remains<=0)|buff.serenity.up",
+                        "Call the Serenity action list if you're using Serenity and Serenity is available (or you're currently in Serenity)" );
+  def -> add_action( "call_action_list,name=sef,if=!talent.serenity.enabled&(buff.storm_earth_and_fire.up|cooldown.storm_earth_and_fire.charges=2)",
+                        "Call the SEF action list if you're using SEF and are currently in SEF or have 2 SEF stacks" );
+  def -> add_action( "call_action_list,name=sef,if=(!talent.serenity.enabled&cooldown.fists_of_fury.remains<=12&chi>=3&cooldown.rising_sun_kick.remains<=1)|target.time_to_die<=25|cooldown.touch_of_death.remains>112",
+                        "Call the SEF action list if you're not using Serenity and:\n# - FoF cd <= 12\n# - Chi >= 3\n# - RSK cd >= 1\n# OR the target will die within 25 seconds OR ToD is on the target" );
+  def -> add_action( "call_action_list,name=sef,if=(!talent.serenity.enabled&cooldown.fists_of_fury.remains<=12&chi>=3&cooldown.rising_sun_kick.remains<=1)|target.time_to_die<=25|cooldown.touch_of_death.remains>112&cooldown.storm_earth_and_fire.charges=1",
+                    "Exactly the same as previous line, but with an added check whether you have 1 stack of SEF" );
+  def -> add_action( "call_action_list,name=sef,if=(!talent.serenity.enabled&!equipped.drinking_horn_cover&cooldown.fists_of_fury.remains<=6&chi>=3&cooldown.rising_sun_kick.remains<=1)|target.time_to_die<=15|cooldown.touch_of_death.remains>112&cooldown.storm_earth_and_fire.charges=1",
+                         "Call the SEF action list if you're using Serenity and:\n# - Using DHC\n# - FoF cd <= 6\n# - Chi >= 3\n# - RSK cd <= 1\n# OR the target will die within 15 seconds OR ToD is on the target and you have 1 stack of SEF" );
+  def -> add_action( "call_action_list,name=aoe,if=active_enemies>3", "Call the AoE action list if there are more than 3 enemies" );
+  def -> add_action( "call_action_list,name=st,if=active_enemies<=3", "Call the ST action list if there are 3 or less enemies" );
+
+  // Cooldowns
+  cd -> add_talent( this, "Invoke Xuen, the White Tiger" );
+
+  // On-use items
+  for ( size_t i = 0; i < items.size(); i++ )
+  {
+    if ( items[i].has_special_effect( SPECIAL_EFFECT_SOURCE_ITEM, SPECIAL_EFFECT_USE ) )
+    {
+      if ( items[i].name_str == "unbridled_fury" )
+         cd -> add_action( "use_item,name=" + items[i].name_str + ",if=(!talent.fist_of_the_white_tiger.enabled&cooldown.fist_of_the_white_tiger.remains<14&cooldown.fists_of_fury.remains<=15&cooldown.rising_sun_kick.remains<7)|buff.serenity.up" );
+      else if ( items[i].name_str == "tiny_oozeling_in_a_jar" )
+        cd -> add_action( "use_item,name=" + items[i].name_str + ",if=buff.congealing_goo.stack>=6" );
+      else if ( items[i].name_str == "horn_of_valor" )
+        cd -> add_action( "use_item,name=" + items[i].name_str + ",if=!talent.serenity.enabled|cooldown.serenity.remains<18|cooldown.serenity.remains>50|target.time_to_die<=30" );
+      else if ( items[i].name_str == "vial_of_ceaseless_toxins" )
+        cd -> add_action( "use_item,name=" + items[i].name_str + ",if=(buff.serenity.up&!equipped.specter_of_betrayal)|(equipped.specter_of_betrayal&(time<5|cooldown.serenity.remains<=8))|!talent.serenity.enabled|target.time_to_die<=cooldown.serenity.remains" );
+      else if ( items[i].name_str == "specter_of_betrayal" )
+        cd -> add_action( "use_item,name=" + items[i].name_str + ",if=(cooldown.serenity.remains>10|buff.serenity.up)|!talent.serenity.enabled" );
+      else if ( ( items[i].name_str != "draught_of_souls" ) || ( items[i].name_str != "forgefiends_fabricator" ) || ( items[i].name_str != "archimondes_hatred_reborn" ) )
+        cd -> add_action( "use_item,name=" + items[i].name_str );
+    }
+  }
+
+  // Racials
+  for ( size_t i = 0; i < racial_actions.size(); i++ )
+  {
+    if ( racial_actions[i] == "arcane_torrent" )
+      cd -> add_action( racial_actions[i] + ",if=chi.max-chi>=1&energy.time_to_max>=0.5", "Use Arcane Torrent if you are missing at least 1 Chi and won't cap energy within 0.5 seconds" );
+    else      cd -> add_action( racial_actions[i] );
+  }
+
+  cd -> add_action( this, "Touch of Death", "target_if=min:debuff.touch_of_death.remains,if=equipped.hidden_masters_forbidden_touch&!prev_gcd.1.touch_of_death",
+                        "Cast ToD cycling through 2 targets if:\n# - You're using HMFT\n# - Your previous GCD was not ToD" );
+  cd -> add_action( this, "Touch of Death", "target_if=min:debuff.touch_of_death.remains,if=((talent.serenity.enabled&cooldown.serenity.remains<=1)&cooldown.fists_of_fury.remains<=4)&cooldown.rising_sun_kick.remains<7&!prev_gcd.1.touch_of_death",
+                        "The second cast of touch_of_death triggered by the legendary effect of hidden_masters_forbidden_touch:\n# - You've already cast the first ToD\n# - SEF is talented and will be available before your next Global Cooldown\n# - Your previous GCD was not ToD\n# - Remaining cooldown on Fist of Fury is lower or equal to 4 seconds\n# - Remaining cooldown on Rising Sun Kick is lower than 7 seconds" );
+  cd -> add_action( this, "Touch of Death", "target_if=min:debuff.touch_of_death.remains,if=(!talent.serenity.enabled&cooldown.storm_earth_and_fire.remains<=1|chi>=2)&|cooldown.fists_of_fury.remains<=4)&cooldown.rising_sun_kick.remains<7&!prev_gcd.1.touch_of_death",
+                        "The second cast of touch_of_death triggered by the legendary effect of hidden_masters_forbidden_touch:\n# - You've already cast the first ToD\n# - Remaining cooldown on Fists of Fury is lower or equal to 4 seconds AND SEF is talented and will be available before your next Global Cooldown OR you have 2 or more Chi\n# - Your previous GCD was not ToD\n# - Remaining cooldown on Rising Sun Kick is greather than 7 seconds" );
+
+  // Storm, Earth, and Fire Opener
+  sef_opener -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1&cooldown.fists_of_fury.remains<=0",
+                                "Cast Tiger Palm in the sef_opener\n# - if the previous ability was not tiger_palm\n# - if the previous ability was not energizing_elixir and you are not at maximum energy\n# - if you have 0 chi\n# - Fists_of_fury is off Cooldown" );
+  sef_opener -> add_action( "call_action_list,name=cd,if=cooldown.fists_of_fury.remains>1",
+                                "Call actions.cd if:\n# - Fist of Fury will be available on your next Global cooldown" );
+  sef_opener -> add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=active_enemies<3" );
+  sef_opener -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=(!prev_gcd.1.blackout_kick)",
+  sef_opener -> add_action( this, "Fists of Fury", "if=cooldown.fists_of_fury.duration>cooldown.rising_sun_kick.remains",
+                                "Cast Fist of Fury if:\n# - The remaining cooldown on rising_sun_kick is longer than the channel duration of Fists_of_fury" );
+  sef_opener -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&chi=1" );
+
+  // Storm, Earth, and Fire
+  sef -> add_action( this, "Tiger Palm", "target_if=debuff.mark_of_the_crane.down,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1" );
+  sef -> add_action( "call_action_list,name=cd" );
+  sef -> add_action( this, "Storm, Earth, and Fire", "if=!buff.storm_earth_and_fire.up" );
+  sef -> add_action( "call_action_list,name=aoe,if=active_enemies>3" );
+  sef -> add_action( "call_action_list,name=st,if=active_enemies<=3" );
+
+  // Serenity Opener
+  serenity_opener -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1&!buff.serenity.up&cooldown.fists_of_fury.remains<=0",
+                                     "Actions.Serenity_Opener is Not Yet Implemented (NYI)" );
+
+  // Serenity Opener Racials
+  for ( size_t i = 0; i < racial_actions.size(); i++ )
+  {
+    if ( racial_actions[i] == "arcane_torrent" )
+      serenity_opener -> add_action( racial_actions[i] + ",if=chi.max-chi>=1&energy.time_to_max>=0.5" );
+  }
+
+  serenity_opener -> add_action( "call_action_list,name=cd,if=cooldown.fists_of_fury.remains>1" );
+  serenity_opener -> add_talent( this, "Serenity", "if=cooldown.fists_of_fury.remains>1" );
+  serenity_opener -> add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=active_enemies<3&buff.serenity.up" );
+  serenity_opener -> add_action( this, "Fist of the White Tiger", "if=buff.serenity.up",
+                                 "Cast Fists_of_fury if\n# - Rising Sun Kicks remaining cooldown is longer than 1 second\n# - Interrupt Fists_of_fury with Rising Sun Kick if Serenity remains" );
+  serenity_opener -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=(!prev_gcd.1.blackout_kick)&(prev_gcd.1.fist_of_the_white_tiger)" );
+  serenity_opener -> add_action( this, "Fists of Fury", "if=cooldown.rising_sun_kick.remains>1|buff.serenity.down,interrupt=1" );
+  serenity_opener -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=buff.serenity.down&chi<=2&cooldown.serenity.remains<=0&prev_gcd.1.tiger_palm" );
+  serenity_opener -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&chi=1" );
+
+  // Serenity
+  serenity -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1&!buff.serenity.up" );
+  serenity -> add_action( "call_action_list,name=cd" );
+  serenity -> add_talent( this, "Serenity" );
+  serenity -> add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=active_enemies<3" );
+  serenity -> add_action( this, "Fist of the White Tiger" );
+  serenity -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=(!prev_gcd.1.blackout_kick)&(prev_gcd.1.fist_of_the_white_tiger|prev_gcd.1.fists_of_fury)&active_enemies<2" );
+  serenity -> add_action( this, "Fists of Fury", "if=((equipped.drinking_horn_cover&buff.pressure_point.remains<=2&set_bonus.tier20_4pc)&(cooldown.rising_sun_kick.remains>1|active_enemies>1)),interrupt=1",
+                              "Legacy syntax for T19/T20 6pc" );
+  serenity -> add_action( this, "Fists of Fury", "if=((!equipped.drinking_horn_cover|buff.bloodlust.up|buff.serenity.remains<1)&(cooldown.rising_sun_kick.remains>1|active_enemies>1)),interrupt=1",
+                              "Cast Fist of Fury if:\n# - The remaining cooldown on rising_sun_kick is longer than the channel duration of Fists_of_fury" );
+  serenity -> add_action( this, "Spinning Crane Kick", "if=active_enemies>=3&!prev_gcd.1.spinning_crane_kick" );
+  serenity -> add_talent( this, "if=talent.rushing_jade_wind.enabled&!prev_gcd.1.rushing_jade_wind&buff.rushing_jade_wind.down&buff.serenity.remains>=4",
+                              "Needs to be rewritten for BFA" );
+  serenity -> add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=active_enemies>=3" );
+  serenity -> add_talent( this, "Rushing Jade Wind", "if=talent.rushing_jade_wind.enabled&!prev_gcd.1.rushing_jade_wind&buff.rushing_jade_wind.down&active_enemies>1",
+                              "Needs to be rewritten for BFA" );
+  serenity -> add_action( this, "Spinning Crane Kick", "if=!prev_gcd.1.spinning_crane_kick" );
+  serenity -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick" );
+
+  // Multiple Targets
+  aoe -> add_action( "call_action_list,name=cd", "Actions.AoE is intended for use with Hectic_Add_Cleave and currently needs to be optimized" );
+  aoe -> add_talent( this, "Energizing Elixir", "if=!prev_gcd.1.tiger_palm&chi<=1&(cooldown.rising_sun_kick.remains=0|(talent.fist_of_the_white_tiger.enabled&cooldown.fist_of_the_white_tiger.remains=0)|energy<50)" );
+
+  // Racials
+  for ( size_t i = 0; i < racial_actions.size(); i++ )
+  {
+    if ( racial_actions[i] == "arcane_torrent" )
+      aoe -> add_action( racial_actions[i] + ",if=chi.max-chi>=1&energy.time_to_max>=0.5" );
+  }
+
+  aoe -> add_action( this, "Fists of Fury", "if=talent.serenity.enabled&!equipped.drinking_horn_cover&cooldown.serenity.remains>=5&energy.time_to_max>2" );
+
+  aoe -> add_action( this, "Fists of Fury", "if=talent.serenity.enabled&equipped.drinking_horn_cover&(cooldown.serenity.remains>=15|cooldown.serenity.remains<=4)&energy.time_to_max>2" );
+  aoe -> add_action( this, "Fists of Fury", "if=!talent.serenity.enabled&energy.time_to_max>2" );
+  aoe -> add_action( this, "Fists of Fury", "if=cooldown.rising_sun_kick.remains>=3.5&chi<=5" );
+  aoe -> add_talent( this, "Whirling Dragon Punch" );
+  aoe -> add_action( this, "Fist of the White Tiger", "if=!talent.serenity.enabled|cooldown.serenity.remains>=10" );
+  aoe -> add_action( this, "Rising Sun Kick", "target_if=cooldown.whirling_dragon_punch.remains>=gcd&!prev_gcd.1.rising_sun_kick&cooldown.fists_of_fury.remains>gcd" );
+  aoe -> add_talent( this, "Rushing Jade Wind", "if=talent.rushing_jade_wind.enabled&!prev_gcd.1.rushing_jade_wind", "Needs to be rewritten for BFA" );
+  aoe -> add_talent( this, "Chi Burst", "if=chi<=3&(cooldown.rising_sun_kick.remains>=5|cooldown.whirling_dragon_punch.remains>=5)&energy.time_to_max>1" );
+  aoe -> add_talent( this, "Chi Burst" );
+  aoe -> add_action( this, "Spinning Crane Kick", "if=(active_enemies>=3|(buff.bok_proc.up&chi.max-chi>=0))&!prev_gcd.1.spinning_crane_kick&set_bonus.tier21_4pc" );
+  aoe -> add_action( this, "Spinning Crane Kick", "if=active_enemies>=3&!prev_gcd.1.spinning_crane_kick" );
+  aoe -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&chi.max-chi>=1&set_bonus.tier21_4pc&(!set_bonus.tier19_2pc|talent.serenity.enabled)" );
+  aoe -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=(chi>1|buff.bok_proc.up|(talent.energizing_elixir.enabled&cooldown.energizing_elixir.remains<cooldown.fists_of_fury.remains))&((cooldown.rising_sun_kick.remains>1&(!talent.fist_of_the_white_tiger.enabled|cooldown.fist_of_the_white_tiger.remains>1)|chi>4)&(cooldown.fists_of_fury.remains>1|chi>2)|prev_gcd.1.tiger_palm)&!prev_gcd.1.blackout_kick" );
+  aoe -> add_action( this, "Crackling Jade Lightning", "if=equipped.the_emperors_capacitor&buff.the_emperors_capacitor.stack>=19&energy.time_to_max>3" );
+  aoe -> add_action( this, "Crackling Jade Lightning", "if=equipped.the_emperors_capacitor&buff.the_emperors_capacitor.stack>=14&cooldown.serenity.remains<13&talent.serenity.enabled&energy.time_to_max>3" );
+  aoe -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&chi.max-chi>=1&set_bonus.tier21_4pc&buff.bok_proc.up" );
+  aoe -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&(chi.max-chi>=2|energy.time_to_max<3)" );
+  aoe -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy.time_to_max<=1&chi.max-chi>=2" );
+  aoe -> add_talent( this, "Chi Wave", "if=chi<=3&(cooldown.rising_sun_kick.remains>=5|cooldown.whirling_dragon_punch.remains>=5)&energy.time_to_max>1" );
+  aoe -> add_talent( this, "Chi Wave" );
+
+  // Single Target
+  st -> add_talent( this, "Invoke Xuen, the White Tiger", "Default action list" );
+  st -> add_action( this, "Storm, Earth, and Fire", "if=!buff.storm_earth_and_fire.up" );
+  st -> add_talent( this, "Energizing Elixir", "if=!prev_gcd.1.tiger_palm" );
+  st -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&chi.max-chi>=1&set_bonus.tier21_4pc&buff.bok_proc.up",
+                        "T21 set bonus conditional\n# Cast Blackout Kick if:\n# - Previous GCD was not Blackout Kick\n# - Blackout Kick! is available\n# - You're not at max Chi" );
+  st -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy.time_to_max<=1&chi.max-chi>=2",
+                        "Cast Tiger Palm if:\n# - Previous GCD was not Tiger Palm\n# - Previous GCD was not EE (NOTE: redundant because of the Energy check, needs to be rewritten for BFA)\n# - You will cap Energy before next GCD\n# - You will gain 2 or more Chi" );
+  st -> add_talent( this, "Fist of the White Tiger", "if=chi.max-chi>=3",
+                        "Cast FotWT if you will gain 3 or more Chi" );
+  st -> add_talent( this, "Whirling Dragon Punch" );
+  st -> add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=((chi>=3&energy>=40)|chi>=5)&(!talent.serenity.enabled|cooldown.serenity.remains>=6)",
+                        "Cast Rising Sun Kick if:\n# - You are using SEF, and you have 3 or more Chi AND 40 or more energy OR 5 or more Chi\n# - You are using Serenity, 6 or more seconds remain on the cooldown of Serenity, and you have 3 or more Chi AND 40 or more energy OR 5 or more Chi " );
+  st -> add_action( this, "Fists of Fury", "if=talent.serenity.enabled&!equipped.drinking_horn_cover&cooldown.serenity.remains>=5&energy.time_to_max>2",
+                        "Legacy conditional for Drinking Horn Cover" );
+  st -> add_action( this, "Fists of Fury", "if=talent.serenity.enabled&equipped.drinking_horn_cover&(cooldown.serenity.remains>=15|cooldown.serenity.remains<=4)&energy.time_to_max>2",
+                        "Legacy conditional for Drinking Horn Cover" );
+  st -> add_action( this, "Fists of Fury", "if=!talent.serenity.enabled",
+                        "Cast Fists of Fury if:\n# - You are using SEF" );
+  st -> add_action( this, "Fists of Fury", "if=cooldown.fists_of_fury.duration<=cooldown.rising_sun_kick.remains",
+                        "Cast Fists of Fury if:\n# - Rising Sun Kick will not come off cooldown during the channel" );
+  st -> add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=(!talent.serenity.enabled|cooldown.serenity.remains>=5)",
+                        "Cast RSK if:\n# - You are using SEF OR you are using Serenity and 5 or more seconds remain on the cooldown of Serenity" );
+  st -> add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&chi.max-chi>=1",
+                    "Cast Blackout Kick if:\n# - Previous GCD was not BoK\n# - You are not at max Chi" );
+  st -> add_action( this, "Crackling Jade Lightning", "if=equipped.the_emperors_capacitor&buff.the_emperors_capacitor.stack>=19&energy.time_to_max>3",
+                        "Legacy for The Emperors Capacitor" );
+  st -> add_action( this, "Crackling Jade Lightning", "if=equipped.the_emperors_capacitor&buff.the_emperors_capacitor.stack>=14&cooldown.serenity.remains<13&talent.serenity.enabled&energy.time_to_max>3" );
+  st -> add_action( this, "Spinning Crane Kick", "if=active_enemies>=3&!prev_gcd.1.spinning_crane_kick",
+                        "Cast spinning_crane_kick if:\n# - Previous cast was not spinning_crane_kick\n# - You have 3 or more active enemies (NOTE: Does not include stacks. May be redundant since actions.st should not be called given the earlier check)" );
+  st -> add_action( this, "Blackout Kick" );
+  st -> add_talent( this, "Chi Burst", "if=chi<=3&(cooldown.rising_sun_kick.remains>=5|cooldown.whirling_dragon_punch.remains>=5)&energy.time_to_max>1",
+                        "Will need to be rewritten for BFA\n# Current rule: Cast Chi Burst if:\n# - You have 3 or less Chi\n# - RSK is up in 5 or more seconds OR WDP is up in 5 or more seconds\n# - You will not cap energy before the next GCD" );
+  st -> add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&(chi.max-chi>=2|energy.time_to_max<3)",
+                        "Cast Tiger Palm if:\n# - Previous ability was not Tiger Palm or Energizing Elixir\n# - You will gain at least 2 Chi, OR you will cap energy within 3 seconds (NOTE: Could cast TP even at 5 Chi just to prevent energy capping, in theory)" );
+  st -> add_talent( this, "Chi Wave" );
+  st -> add_talent( this, "Chi Burst" );
+}
