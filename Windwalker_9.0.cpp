// TODO:
// Windwalker
// - Remove old Touch of Death calls
// - Resource talents need to be looked at. Seem to be poorly optimized.

// Some Changes
// - Added raid event delay for ChiX implementation in the future and better holding prior to adds.
// Storm, Earth, and Fire should be casting the correct number of abilities inside the duration window. Needs to be double checked at different haste levels.

// Windwalker Combat Action Priority List ===============================

void monk_t::apl_combat_windwalker()
{
  std::vector<std::string> racial_actions = get_racial_actions();
  action_priority_list_t* def             = get_action_priority_list( "default" );
  action_priority_list_t* cd_sef          = get_action_priority_list( "cd_sef" );
  action_priority_list_t* cd_serenity     = get_action_priority_list( "cd_serenity" );
  action_priority_list_t* serenity        = get_action_priority_list( "serenity" );
  action_priority_list_t* aoe             = get_action_priority_list( "aoe" );
  action_priority_list_t* st              = get_action_priority_list( "st" );

  def->add_action( "auto_attack" );
  def->add_action( this, "Spear Hand Strike", "if=target.debuff.casting.react" );
  def->add_action( this, "Touch of Karma", "interval=90,pct_health=0.5" );

  if ( sim->allow_potions )
  {
    if ( true_level >= 100 )
      def->add_action(
          "potion,if=buff.serenity.up|buff.storm_earth_and_fire.up|target.time_to_die<=60",
          "Use potion if either Serenity or Storm, Earth, and Fire is up or the target will die within 60 seconds." );
    else
      def->add_action(
          "potion,if=buff.serenity.up|buff.storm_earth_and_fire.up|(!talent.serenity.enabled&trinket.proc.agility."
          "react)"
          "|buff.bloodlust.react|target.time_to_die<=60"
        "Alternate potion use: react to a main stat trinket proc if Serenity is enabled, Bloodlust, or if the target will die within 60 seconds and Serenity or Storm, Earth, and Fire are up.");
  }

  def->add_action(
      this, spec.reverse_harm, "reverse_harm",
      "if=chi.max-chi>=2&(talent.serenity.enabled|!dot.touch_of_death.remains)&buff.serenity.down&(energy.time_to_max<"
      "1|talent.serenity.enabled&cooldown.serenity.remains<2|!talent.serenity.enabled&cooldown.touch_of_death.remains<"
      "3&!variable.hold_tod|energy.time_to_max<4&cooldown.fists_of_fury.remains<1.5)" );
  def->add_talent(
      this, "Fist of the White Tiger",
      "target_if=min:debuff.mark_of_the_crane.remains,if=chi.max-chi>=3&buff.serenity.down&buff.seething_rage.down&("
      "energy.time_to_max<1|talent.serenity.enabled&cooldown.serenity.remains<2|!talent.serenity.enabled&cooldown."
      "touch_of_death.remains<3&!variable.hold_tod|energy.time_to_max<4&cooldown.fists_of_fury.remains<1.5)",
      "Use FotWT if  you are missing at least 3 chi, And  serenity, And  BotE are not up, AND you either are about to "
      "cap energy, or serenity is about to come up, or ToD is about to come up, or FoF is coming up and you will cap "
      "energy soon" );
  def->add_action( this, "Tiger Palm",
                   "target_if=min:debuff.mark_of_the_crane.remains,if=!combo_break&chi.max-chi>=2&(talent.serenity."
                   "enabled|!dot.touch_of_death.remains|active_enemies>2)&buff.seething_rage.down&buff.serenity.down&(energy.time_to_"
                   "max<1|talent.serenity.enabled&cooldown.serenity.remains<2|!talent.serenity.enabled&cooldown.touch_"
                   "of_death.remains<3&!variable.hold_tod|energy.time_to_max<4&cooldown.fists_of_fury.remains<1.5)",
                   "Use TP if it wont break mastery, AND are missing at least 2 chi, AND big cooldowns are not up, AND "
                   "you either are about to cap energy, or serenity is about to come up, or ToD is coming up, or FoF "
                   "is coming up and you will cap energy soon" );
  def->add_talent( this, "Chi Wave", "if=!talent.fist_of_the_white_tiger.enabled&prev_gcd.1.tiger_palm&time<=3" );
  def->add_action( "call_action_list,name=cd_serenity,if=talent.serenity.enabled" );
  def->add_action( "call_action_list,name=cd_sef,if=!talent.serenity.enabled" );
  def->add_action( "call_action_list,name=serenity,if=buff.serenity.up",
                   "Call the Serenity action list if Serenity is currently up" );
  def->add_action( "call_action_list,name=st,if=active_enemies<3",
                   "Call the ST action list if there are 2 or less enemies" );
  def->add_action( "call_action_list,name=aoe,if=active_enemies>=3",
                   "Call the AoE action list if there are 3 or more enemies" );

  // Serenity Cooldowns
  cd_serenity->add_talent( this, "Invoke Xuen, the White Tiger", "if=buff.serenity.down|target.time_to_die<25",
                           "Cooldowns" );

  // Serenity On-use w/ Azshara's Font of Power
  for ( size_t i = 0; i < items.size(); i++ )
  {
    if ( items[ i ].has_special_effect( SPECIAL_EFFECT_SOURCE_ITEM, SPECIAL_EFFECT_USE ) )
    {
      if ( items[ i ].name_str == "azsharas_font_of_power" )
        cd_serenity->add_action( "use_item,name=" + items[ i ].name_str + ",if=buff.serenity.down&(cooldown.serenity.remains<20|target.time_to_die<40)" );
    }
  }

  cd_serenity->add_action(
      "guardian_of_azeroth,if=buff.serenity.down&(target.time_to_die>185|cooldown.serenity.remains<=7)|target.time_to_"
      "die<35" );

  // Serenity Racials
  for ( size_t i = 0; i < racial_actions.size(); i++ )
  {
    if ( racial_actions[ i ] == "arcane_torrent" )
      cd_serenity->add_action( racial_actions[ i ] + ",if=buff.serenity.down&chi.max-chi>=1&energy.time_to_max>=0.5",
                               "Use Arcane Torrent if Serenity is not up, and you are missing at least 1 Chi, and "
                               "won't cap energy within 0.5 seconds" );
    else if ( racial_actions[ i ] == "ancestral_call" )
      cd_serenity->add_action( racial_actions[ i ] + ",if=cooldown.serenity.remains>20|target.time_to_die<20" );
    else if ( racial_actions[ i ] == "blood_fury" )
      cd_serenity->add_action( racial_actions[ i ] + ",if=cooldown.serenity.remains>20|target.time_to_die<20" );
    else if ( racial_actions[ i ] == "fireblood" )
      cd_serenity->add_action( racial_actions[ i ] + ",if=cooldown.serenity.remains>20|target.time_to_die<10" );
    else if ( racial_actions[ i ] == "berserking" )
      cd_serenity->add_action( racial_actions[ i ] + ",if=cooldown.serenity.remains>20|target.time_to_die<15" );
    else
      cd_serenity->add_action( racial_actions[ i ] );
  }

  // Serenity On-use w/ Lustrous Golden Plumage & Gladiator's Medallion
  for ( size_t i = 0; i < items.size(); i++ )
  {
    if ( items[ i ].has_special_effect( SPECIAL_EFFECT_SOURCE_ITEM, SPECIAL_EFFECT_USE ) )
    {
      if ( items[ i ].name_str == "lustrous_golden_plumage" )
        cd_serenity->add_action( "use_item,name=" + items[ i ].name_str + ",if=cooldown.touch_of_death.remains<1|cooldown.touch_of_death.remains>20|!variable.hold_tod|target.time_to_die<25" );
      else if ( items[ i ].name_str == "gladiators_medallion" )
        cd_serenity->add_action( "use_item,name=" + items[ i ].name_str + ",if=cooldown.touch_of_death.remains<1|cooldown.touch_of_death.remains>20|!variable.hold_tod|target.time_to_die<20" );
    }
  }

  cd_serenity->add_action( this, "Touch of Death", "if=!variable.hold_tod" );

  // Serenity On-use w/ Pocketsized Computation Device
  for ( size_t i = 0; i < items.size(); i++ )
  {
    if ( items[ i ].has_special_effect( SPECIAL_EFFECT_SOURCE_ITEM, SPECIAL_EFFECT_USE ) )
    {
      if ( items[ i ].name_str == "pocketsized_computation_device" )
        cd_serenity->add_action( "use_item,name=" + items[ i ].name_str + ",if=buff.serenity.down&(cooldown.touch_of_death.remains>10|!variable.hold_tod)|target.time_to_die<5" );
    }
  }

  cd_serenity->add_action(
      "blood_of_the_enemy,if=buff.serenity.down&(cooldown.serenity.remains>20|cooldown.serenity.remains<2)|target.time_"
      "to_die<15" );

   // Serenity On-use items
  for ( size_t i = 0; i < items.size(); i++ )
  {
    std::string name_str = "";
    if ( items[ i ].has_special_effect( SPECIAL_EFFECT_SOURCE_ITEM, SPECIAL_EFFECT_USE ) )
    {
      name_str = items[ i ].name_str;
      if ( name_str != "azsharas_font_of_power" || name_str != "lustrous_golden_plumage" ||
           name_str != "gladiators_medallion" || name_str != "pocketsized_computation_device" )
      {
        if ( name_str == "remote_guidance_device" )
          cd_serenity->add_action( "use_item,name=" + name_str +
                                   ",if=cooldown.touch_of_death.remains>10|!variable.hold_tod" );
        else if ( name_str == "gladiators_badge" )
          cd_serenity->add_action( "use_item,name=" + name_str +
                                   ",if=cooldown.serenity.remains>20|target.time_to_die<20" );
        else if ( name_str == "galecallers_boon" )
          cd_serenity->add_action( "use_item,name=" + name_str +
                                   ",if=cooldown.serenity.remains>20|target.time_to_die<20" );
        else if ( name_str == "writhing_segment_of_drestagath" )
          cd_serenity->add_action( "use_item,name=" + name_str +
                                   ",if=cooldown.touch_of_death.remains>10|!variable.hold_tod" );
        else if ( name_str == "ashvanes_razor_coral" )
          cd_serenity->add_action( "use_item,name=" + name_str +
                                   ",if=debuff.razor_coral_debuff.down|buff.serenity.remains>9|target.time_to_die<25" );
        else
          cd_serenity->add_action( "use_item,name=" + name_str );
      }
    }
  }

  // Serenity Essences
  cd_serenity->add_action( "worldvein_resonance,if=buff.serenity.down&(cooldown.serenity.remains>15|cooldown.serenity.remains<2)|target.time_to_die<20" );
  cd_serenity->add_action(
      "concentrated_flame,if=buff.serenity.down&(cooldown.serenity.remains|cooldown.concentrated_flame.charges=2)&!dot.concentrated_flame_burn.remains&(cooldown.rising_sun_kick.remains&cooldown.fists_of_fury.remains|target.time_to_die<8)" );

  cd_serenity->add_talent( this, "Serenity" );

  cd_serenity->add_action( "the_unbound_force,if=buff.serenity.down" );
  cd_serenity->add_action( "purifying_blast,if=buff.serenity.down" );
  cd_serenity->add_action( "reaping_flames,if=buff.serenity.down" );
  cd_serenity->add_action( "focused_azerite_beam,if=buff.serenity.down" );
  cd_serenity->add_action( "memory_of_lucid_dreams,if=buff.serenity.down&energy<40" );
  cd_serenity->add_action( "ripple_in_space,if=buff.serenity.down" );
  cd_serenity->add_action( "bag_of_tricks,if=buff.serenity.down" );

  // Storm, Earth and Fire Cooldowns
  cd_sef->add_talent( this, "Invoke Xuen, the White Tiger", "if=buff.serenity.down|target.time_to_die<25",
                           "Cooldowns" );

  // Storm, Earth, and Fire w/ Azshara's Font of Power
  for ( size_t i = 0; i < items.size(); i++ )
  {
    if ( items[ i ].has_special_effect( SPECIAL_EFFECT_SOURCE_ITEM, SPECIAL_EFFECT_USE ) )
    {
      if ( items[ i ].name_str == "azsharas_font_of_power" )
        cd_sef->add_action( "use_item,name=" + items[ i ].name_str + ",if=buff.storm_earth_and_fire.down&!dot.touch_of_death.remains&(cooldown.touch_of_death.remains<15|cooldown.touch_of_death.remains<21&(variable.tod_on_use_trinket|equipped.ashvanes_razor_coral)|variable.hold_tod|target.time_to_die<40)" );
    }
  }

  cd_sef->add_action(
      "guardian_of_azeroth,if=target.time_to_die>185|!variable.hold_tod&cooldown.touch_of_death.remains<=14|target.time_to_die<35" );
  cd_sef->add_action(
      "worldvein_resonance,if=cooldown.touch_of_death.remains>58|cooldown.touch_of_death.remains<2|variable.hold_tod|target.time_to_die<20" );

  // Storm, Earth, and Fire w/ Arcane Torrent
  for ( size_t i = 0; i < racial_actions.size(); i++ )
  {
    if ( racial_actions[ i ] == "arcane_torrent" )
      cd_sef->add_action( racial_actions[ i ] + ",if=chi.max-chi>=1&energy.time_to_max>=0.5",
                               "Use Arcane Torrent if you are missing at least 1 Chi and won't cap energy within 0.5 seconds" );
  }

  // Storm, Earth, and Fire w/ Lustrous Golden Plumage & Gladiator's Medallion
  for ( size_t i = 0; i < items.size(); i++ )
  {
    if ( items[ i ].has_special_effect( SPECIAL_EFFECT_SOURCE_ITEM, SPECIAL_EFFECT_USE ) )
    {
      if ( items[ i ].name_str == "lustrous_golden_plumage" )
        cd_sef->add_action( "use_item,name=" + items[ i ].name_str +
                                 ",if=cooldown.touch_of_death.remains<1|cooldown.touch_of_death.remains>20|!variable."
                                 "hold_tod|target.time_to_die<25" );
      else if ( items[ i ].name_str == "gladiators_medallion" )
        cd_sef->add_action( "use_item,name=" + items[ i ].name_str +
                                 ",if=cooldown.touch_of_death.remains<1|cooldown.touch_of_death.remains>20|!variable."
                                 "hold_tod|target.time_to_die<20" );
    }
  }

  cd_sef->add_action( this, "Touch of Death", "if=!variable.hold_tod&(!equipped.cyclotronic_blast|cooldown.cyclotronic_blast.remains<=1)&(chi>1|energy<40)" );
  cd_sef->add_action( this, "Storm, Earth, and Fire", ",if=cooldown.storm_earth_and_fire.charges=2|dot.touch_of_death.remains|target.time_to_die<20|(buff.worldvein_resonance.remains>10|cooldown.worldvein_resonance.remains>cooldown.storm_earth_and_fire.full_recharge_time|!essence.worldvein_resonance.major)&(cooldown.touch_of_death.remains>cooldown.storm_earth_and_fire.full_recharge_time|variable.hold_tod&!equipped.dribbling_inkpod)&cooldown.fists_of_fury.remains<=9&chi>=3&cooldown.whirling_dragon_punch.remains<=14|&cooldown.rising_sun_kick.remains<=4 );
  // cd_sef->add_action( this, "Storm, Earth, and Fire", "if=storm_earth_and_fire,target=1|(debuff.storm_earth_and_fire_target.down|!equipped.Coordinated_Offensive)" "Reminder for future conduit implementation"
  cd_sef->add_action( "blood_of_the_enemy,if=cooldown.touch_of_death.remains>45|variable.hold_tod&cooldown.fists_of_fury.remains<2|target.time_to_die<12|target.time_to_die>100&target.time_to_die<110&(cooldown.fists_of_fury.remains<3|cooldown.whirling_dragon_punch.remains<5|cooldown.rising_sun_kick.remains<5)" );
  cd_sef->add_action( "concentrated_flame,if=!dot.concentrated_flame_burn.remains&((cooldown.concentrated_flame.remains<=cooldown.touch_of_death.remains+1|variable.hold_tod)&(!talent.whirling_dragon_punch.enabled|cooldown.whirling_dragon_punch.remains)&cooldown.rising_sun_kick.remains&cooldown.fists_of_fury.remains&buff.storm_earth_and_fire.down|dot.touch_of_death.remains)|target.time_to_die<8" );

  // Storm, Earth and Fire Racials
  for ( size_t i = 0; i < racial_actions.size(); i++ )
  {
    if ( racial_actions[ i ] != "arcane_torrent" )
    {
      if ( racial_actions[ i ] == "ancestral_call" )
        cd_sef->add_action( racial_actions[ i ] + ",if=cooldown.touch_of_death.remains>30|variable.hold_tod|target.time_to_die<20" );
      else if ( racial_actions[ i ] == "blood_fury" )
        cd_sef->add_action( racial_actions[ i ] + ",if=cooldown.touch_of_death.remains>30|variable.hold_tod|target.time_to_die<20", "Use Blood Fury if Touch of Death's cooldown is greater than 30 (this includes while ToD is currently active), or off cooldown when you are holding onto ToD, or when the target is about to die" );
      else if ( racial_actions[ i ] == "fireblood" )
        cd_sef->add_action( racial_actions[ i ] + ",if=cooldown.touch_of_death.remains>30|variable.hold_tod|target.time_to_die<10" );
      else if ( racial_actions[ i ] == "berserking" )
        cd_sef->add_action( racial_actions[ i ] + ",if=cooldown.touch_of_death.remains>30|variable.hold_tod|target.time_to_die<15" );
      else
            cd_sef->add_action( racial_actions[ i ] );
    }
  }

  // Storm, Earth and Fire On-use items
  for ( size_t i = 0; i < items.size(); i++ )
  {
    std::string name_str = "";
    if ( items[ i ].has_special_effect( SPECIAL_EFFECT_SOURCE_ITEM, SPECIAL_EFFECT_USE ) )
    {
      name_str = items[ i ].name_str;
      if ( name_str != "azsharas_font_of_power" || name_str != "lustrous_golden_plumage" || name_str != "gladiators_medallion" )
      {
        if ( name_str == "pocketsized_computation_device" )
          cd_sef->add_action( "use_item,name=" + name_str + ",,if=cooldown.touch_of_death.remains>30|!variable.hold_tod" );
        else if ( name_str == "remote_guidance_device" )
          cd_sef->add_action( "use_item,name=" + name_str + ",if=cooldown.touch_of_death.remains>30|!variable.hold_tod" );
        else if ( name_str == "gladiators_badge" )
          cd_sef->add_action( "use_item,name=" + name_str + ",if=cooldown.touch_of_death.remains>20|!variable.hold_tod|target.time_to_die<20" );
        else if ( name_str == "galecallers_boon" )
          cd_sef->add_action( "use_item,name=" + name_str + ",if=cooldown.touch_of_death.remains>55|variable.hold_tod|target.time_to_die<12" );
        else if ( name_str == "writhing_segment_of_drestagath" )
          cd_sef->add_action( "use_item,name=" + name_str + ",if=cooldown.touch_of_death.remains>20|!variable.hold_tod" );
        else if ( name_str == "ashvanes_razor_coral" )
        {
          cd_sef->add_action( "use_item,name=" + name_str + ",if=variable.tod_on_use_trinket&(cooldown.touch_of_death.remains>21|variable.hold_tod)&(debuff.razor_coral_debuff.down|buff.storm_earth_and_fire.remains>13|target.time_to_die-cooldown.touch_of_death.remains<40&cooldown.touch_of_death.remains<25|target.time_to_die<25)" );
          cd_sef->add_action( "use_item,name=" + name_str + ",if=!variable.tod_on_use_trinket&(debuff.razor_coral_debuff.down|(!equipped.dribbling_inkpod|target.time_to_pct_30.remains<8)&(dot.touch_of_death.remains|cooldown.touch_of_death.remains+9>target.time_to_die)&buff.storm_earth_and_fire.up|target.time_to_die<25)" );
                }
        else
          cd_sef->add_action( "use_item,name=" + name_str );
      }
    }
  }

  // Storm, Earth and Fire Essences
  cd_sef->add_action( "the_unbound_force" );
  cd_sef->add_action( "purifying_blast" );
  cd_sef->add_action( "reaping_flames" );
  cd_sef->add_action( "focused_azerite_beam" );
  cd_sef->add_action( "memory_of_lucid_dreams,if=energy<40" );
  cd_sef->add_action( "ripple_in_space" );
  cd_sef->add_action( "bag_of_tricks" );

  // Serenity
  serenity->add_action( this, "Fists of Fury", "if=buff.serenity.remains<1|active_enemies>1", "Priority while serenity is up" );
  serenity->add_action( this, "Spinning Crane Kick", "if=combo_strike&(active_enemies>2|active_enemies>1&!cooldown.rising_sun_kick.up)" );
  serenity->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=combo_strike" );
  serenity->add_action( this, "Fists of Fury", "interrupt_if=gcd.remains=0", "This will cast FoF and interrupt the channel if the GCD is ready and something higher on the priority list (RSK) is avaible" );
  serenity->add_talent( this, "Fist of the White Tiger", "target_if=min:debuff.mark_of_the_crane.remains,if=chi<3" );
  serenity->add_action( this, spec.reverse_harm, "reverse_harm", "if=chi.max-chi>1&energy.time_to_max<1" );
  serenity->add_action( this, "Blackout Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=combo_strike|!talent.hit_combo.enabled", "Use BoK, it will only break mastery if Hit Combo is NOT talented" );
  serenity->add_action( this, "Spinning Crane Kick" );

  // Multiple Targets
  aoe->add_talent( this, "Whirling Dragon Punch", "if=active_enemies>1&(!raid_event.adds.exists|raid_event.adds.up)," "Actions.AoE is intended for use with Hectic_Add_Cleave and currently needs to be optimized" );
  aoe->add_talent( this, "Energizing Elixir", "if=!prev_gcd.1.tiger_palm&chi<=1&energy<50" );
  aoe->add_action( this, "Fists of Fury", "if=energy.time_to_max>1" );
  aoe->add_action( this, "Rising Sun Kick",
                   "target_if=min:debuff.mark_of_the_crane.remains,if=(talent.whirling_dragon_punch.enabled&cooldown.rising_sun_kick.duration>cooldown.whirling_dragon_punch.remains+4)&(cooldown.fists_of_fury.remains>3|chi>=5)" );
  aoe->add_talent( this, "Rushing Jade Wind", "if=buff.rushing_jade_wind.down" );
  aoe->add_action( this, "Spinning Crane Kick",
                   "if=combo_strike&(((chi>3|cooldown.fists_of_fury.remains>6)&(chi>=5|cooldown.fists_of_fury.remains>2))|energy.time_to_max<=3|buff.dance_of_chiji.react)" );
  aoe->add_action( this, spec.reverse_harm, "reverse_harm", "if=chi.max-chi>=2" );
  aoe->add_talent( this, "Chi Burst", "if=chi.max-chi>=3" );
  aoe->add_talent( this, "Fist of the White Tiger", "target_if=min:debuff.mark_of_the_crane.remains,if=chi.max-chi>=3" );
  aoe->add_action( this, "Tiger Palm",
                                   "target_if=min:debuff.mark_of_the_crane.remains,if=chi.max-chi>=2&(!talent.hit_combo.enabled|!combo_break)" );
  aoe->add_talent( this, "Chi Wave", "if=!combo_break" );
  aoe->add_action( this, "Flying Serpent Kick", "if=buff.bok_proc.down,interrupt=1" );
  aoe->add_action( this, "Blackout Kick",
                   "target_if=min:debuff.mark_of_the_crane.remains,if=combo_strike&(buff.bok_proc.up|(talent.hit_combo.enabled&prev_gcd.1.tiger_palm&chi<4))" );

  // Single Target
  st->add_talent( this, "Whirling Dragon Punch","if=raid_event.adds.in>24|buff.storm_earth_and_fire.remains<=1" "", "Single target priority but holds if Adds will spawn before its off cooldown. Helps to transition into AoE.APL" );
  st->add_talent( this, "Whirling Dragon Punch","if=raid_event.adds.in>24|cooldown.storm_earth_and_fire.recharge_time>20" "", "Single target priority but holds if Adds will spawn before its off cooldown. Helps to transition into AoE.APL" );
  st->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=chi>=5", "Should fix the RSK / FoF overlap prio"
  st->add_action( this, "Fists of Fury", "if=talent.serenity.enabled|cooldown.touch_of_death.remains>6|variable.hold_tod|raid_event.adds.in>cooldown" ); "Again, holds if Adds will spawn before its off cooldown but slightly different to account for BoK CDR. Helps to transition into AoE.APL""
  st->add_action( this, "Rising Sun Kick", "target_if=min:debuff.mark_of_the_crane.remains,if=cooldown.touch_of_death.remains>2|variable.hold_tod", "Use RSK on targets without Mark of the Crane debuff, if possible, and if ToD is at least 2 seconds away" );
  st->add_talent( this, "Rushing Jade Wind", "if=buff.rushing_jade_wind.down&active_enemies>1" );
  st->add_action( this, spec.reverse_harm, "reverse_harm", "if=chi.max-chi>1" );
  st->add_talent( this, "Fist of the White Tiger", "target_if=min:debuff.mark_of_the_crane.remains,if=chi<3" );
  st->add_talent( this, "Energizing Elixir", "if=chi<=3&energy<50" );
  st->add_talent( this, "Chi Burst", "if=chi.max-chi>0&active_enemies=1|chi.max-chi>1", "Use CB if you are more than 0 Chi away from max and have 1 enemy, or are more than 1 Chi away from max" );
  st->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=combo_strike&chi.max-chi>3&buff.storm_earth_and_fire.down", "Use TP if you are 4 or more chi away from max and ToD and SEF are both not up" );
  st->add_talent( this, "Chi Wave" );
  st->add_action( this, "Spinning Crane Kick", "if=combo_strike&buff.dance_of_chiji.react" );
  // st->add_action( this, "Spinning Crane Kick", "if=combo_strike|spinning_crane_kick.count>3&!equipped.Calculated_Strikes|buff.Weapons_of_Order	" ); "3 is Arbitrary. I think at 2 it deals equal damage to a BOK with the conduit. Main difference is the Chi Cost during the buff"
  st->add_action( this, "Blackout Kick",
                  "target_if=min:debuff.mark_of_the_crane.remains,if=combo_strike&((cooldown.touch_of_death.remains>2|variable.hold_tod)&(cooldown.rising_sun_kick.remains>2&cooldown.fists_of_fury.remains>2|cooldown.rising_sun_kick.remains<3&cooldown.fists_of_fury.remains>3&chi>2|cooldown.rising_sun_kick.remains>3&cooldown.fists_of_fury.remains<3&chi>4|chi>5)|buff.bok_proc.up)",
                  "Use BoK if both FoF and RSK are not close, or RSK is close and FoF is not close and you have more than 2 chi, or FoF is close RSK is not close and you have more than 3 chi, or you have more than 5 chi, or if you get a proc" );
  st->add_action( this, "Tiger Palm", "target_if=min:debuff.mark_of_the_crane.remains,if=combo_strike&chi.max-chi>1" );
  st->add_action( this, "Flying Serpent Kick", "interrupt=1", "Use FSK and interrupt it straight away" );
  st->add_action( this, "Blackout Kick",
                  "target_if=min:debuff.mark_of_the_crane.remains,if=(cooldown.fists_of_fury.remains<3&chi=2|energy.time_to_max<1)&(prev_gcd.1.tiger_palm|chi.max-chi<2)",
                  "Use BoK if FoF is close and you have 2 chi and your last global was TP, or if you are about to cap energy and either your last gcd was TP or if you are less than 2 chi away from capping" );

}
