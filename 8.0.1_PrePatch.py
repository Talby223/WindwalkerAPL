# Default consumables
#potion=prolonged_power
#flask=seventh_demon
#food=lavish_suramar_feast
#augmentation=defiled

# This default action priority list is automatically created based on your character.
# It is a attempt to provide you with a action list that is both simple and practicable,
# while resulting in a meaningful and good simulation. It may not result in the absolutely highest possible dps.
# Feel free to edit, adapt and improve it to your own needs.
# SimulationCraft is always looking for updates and improvements to the default action lists.

# Executed before combat begins. Accepts non-harmful actions only.
actions.precombat=flask
actions.precombat+=/food
actions.precombat+=/augmentation
# Snapshot raid buffed stats before combat begins and pre-potting is done.
actions.precombat+=/snapshot_stats
actions.precombat+=/potion
actions.precombat+=/chi_burst
actions.precombat+=/chi_wave

# Executed every time the actor is available.
call_action_list
actions=auto_attack
actions+=/spear_hand_strike,if=target.debuff.casting.react
#Touch of Karma on cooldown, if Good Karma is enabled equal to 100% of maximum health
actions+=/touch_of_karma,if=!talent.good_karma.enabled,interval=90,pct_health=0.5
actions+=/touch_of_karma,if=talent.good_karma.enabled,interval=90,pct_health=1.0
#Potion if Serenity or Storm, Earth, and Fire are up or you are running SEF and a main stat trinket procs, or you are under the effect of bloodlust, or target time to die is lower or equal to 60
actions+=/potion,if=buff.serenity.up|buff.storm_earth_and_fire.up|(!talent.serenity.enabled&trinket.proc.agility.react)|buff.bloodlust.react|target.time_to_die<=60
actions+=/touch_of_death,if=target.time_to_die<=9
# Call the Serenity action list if you're using Serenity and Serenity is available (or you're currently in Serenity)
actions+=/call_action_list,name=serenity,if=(talent.serenity.enabled&cooldown.serenity.remains<=0)|buff.serenity.up
# Call the SEF action list if you're using SEF and are currently in SEF or have 2 SEF stacks
actions+=/call_action_list,name=sef,if=!talent.serenity.enabled&(buff.storm_earth_and_fire.up|cooldown.storm_earth_and_fire.charges=2)

# Call the SEF action list if you're using SEF and:
# - FoF cd <= 12
# - Chi >= 3
# - RSK cd >= 1
# OR the target will die within 25 seconds OR ToD is on the target
actions+=/call_action_list,name=sef,if=!talent.serenity.enabled&cooldown.fists_of_fury.remains<=12&chi>=3&cooldown.rising_sun_kick.remains<=1|target.time_to_die<=25|cooldown.touch_of_death.remains>112)

# Exactly the same as previous line, but with an added check whether you have 1 stack of SEF
actions+=/call_action_list,name=sef,if=!talent.serenity.enabled&cooldown.fists_of_fury.remains<=12&chi>=3&cooldown.rising_sun_kick.remains<=1|target.time_to_die<=25|cooldown.touch_of_death.remains>112)&cooldown.storm_earth_and_fire.charges=1

# Call the SEF action list if you're using SEF and:
# - You're not using DHC
# - FoF cd <= 6
# - Chi >= 3
# - RSK cd <= 1
# OR the target will die within 15 seconds OR ToD is on the target and you have 1 stack of SEF
actions+=/call_action_list,name=sef,if=!talent.serenity.enabled&!equipped.drinking_horn_cover&&cooldown.fists_of_fury.remains<=6&chi>=3&cooldown.rising_sun_kick.remains<=1|target.time_to_die<=15|cooldown.touch_of_death.remains>112)&cooldown.storm_earth_and_fire.charges=1
# Call the AoE action list if there are more than 3 enemies
actions+=/call_action_list,name=aoe,if=active_enemies>3*
# Call the ST action list if there are 3 or less enemies
actions+=/call_action_list,name=st,if=active_enemies<=3

# Action list of all cooldowns to pop when called
actions.cd=invoke_xuen_the_white_tiger
actions.cd+=/blood_fury
actions.cd+=/berserking
# Use Arcane Torrent if you are missing at least 1 Chi and won't cap energy within 0.5 seconds
actions.cd+=/arcane_torrent,if=chi.max-chi>=1&energy.time_to_max>=0.5
actions.cd+=/lights_judgment
# Cast ToD cycling through 2 targets if:
# - NOTE: I suspect "if=!artifact.gale_burst.enabled" checks whether you've already cast the first ToD.
# - You're using HMFT
# - Your previous GCD was not ToD
actions.cd+=/touch_of_death,cycle_targets=1,max_cycle_targets=2,if=!artifact.gale_burst.enabled&equipped.hidden_masters_forbidden_touch&!prev_gcd.1.touch_of_death

#Cast ToD if you're not using HMFT (and you haven't cast ToD yet, redundant)
actions.cd+=/touch_of_death,if=!artifact.gale_burst.enabled&!equipped.hidden_masters_forbidden_touch

# The second cast of touch_of_death triggered by the legendary effect of hidden_masters_forbidden_touch:
# - You've already cast the first ToD
# - SEF is talented and will be available before your next Global Cooldown
# - Your previous GCD was not ToD
# - Remaining cooldown on Fist of Fury is lower or equal to 4 seconds
# - Remaining cooldown on Rising Sun Kick is lower than 7 seconds
actions.cd+=/touch_of_death,cycle_targets=1,max_cycle_targets=2,if=artifact.gale_burst.enabled&((talent.serenity.enabled&cooldown.serenity.remains<=1)&|cooldown.fists_of_fury.remains<=4)&cooldown.rising_sun_kick.remains<7&!prev_gcd.1.touch_of_death

# The second cast of touch_of_death triggered by the legendary effect of hidden_masters_forbidden_touch:
# - You've already cast the first ToD
# - Remaining cooldown on Fists of Fury is lower or equal to 4 seconds AND SEF is talented and will be available before your next Global Cooldown OR you have 2 or more Chi
# - Your previous GCD was not ToD
# - Remaining cooldown on Rising Sun Kick is greather than 7 seconds
actions.cd+=/touch_of_death,cycle_targets=1,max_cycle_targets=2,if=artifact.gale_burst.enabled&(talent.storm_earth_and_fire.enabled&cooldown.storm_earth_and_fire.remains<=1|chi>=2)&|cooldown.fists_of_fury.remains<=4)&cooldown.rising_sun_kick.remains<7&!prev_gcd.1.touch_of_death

# Actions.SeF_Opener is Not Yet Implemented (NYI)
actions.sef_opener=tiger_palm,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1&cooldown.fists_of_fury.remains<=0
# Cast Tiger Palm in the sef_opener
# - if the previous ability was not tiger_palm
# - if the previous ability was not energizing_elixir and you are not at maximum energy
# - if you have 0 chi
# - Fists_of_fury is off Cooldown
actions.sef_opener+=/arcane_torrent,if=chi.max-chi>=1&energy.time_to_max>=0.5
# Cast Arcane Torrent if
# - You will not cap Chi or cap energy in the next .5 seconds
actions.sef_opener+=/call_action_list,name=cd,if=cooldown.fists_of_fury.remains>1
# Call actions.cd if:
# - Fist of Fury will be available on your next Global cooldown
actions.sef_opener+=/rising_sun_kick,target_if=min:debuff.mark_of_the_crane.remains,if=active_enemies<3
actions.sef_opener+=/blackout_kick,target_if=min:debuff.mark_of_the_crane.remains,if=(!prev_gcd.1.blackout_kick)
#This line is outdated and probably incorrect in priority
    actions.sef_opener+=/fists_of_fury,if=cooldown.fists_of_fury.duration>cooldown.rising_sun_kick.remains
# Cast Fist of Fury if:
# - The remaining cooldown on rising_sun_kick is longer than the channel duration of Fists_of_fury
actions.sef_opener+=/tiger_palm,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&chi=1
actions.sef=tiger_palm,target_if=debuff.mark_of_the_crane.down,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1
actions.sef+=/arcane_torrent,if=chi.max-chi>=1&energy.time_to_max>=0.5
actions.sef+=/call_action_list,name=cd
actions.sef+=/storm_earth_and_fire,if=!buff.storm_earth_and_fire.up
# Do not fixate storm_earth_and_fire on your current target
actions.sef+=/call_action_list,name=aoe,if=active_enemies>3
actions.sef+=/call_action_list,name=st,if=active_enemies<=3

# Actions.Serenity_Opener is Not Yet Implemented (NYI)
actions.serenity_opener=tiger_palm,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1&!buff.serenity.up&cooldown.fists_of_fury.remains<=0
actions.serenity_opener+=/arcane_torrent,if=chi.max-chi>=1&energy.time_to_max>=0.5
actions.serenity_opener+=/call_action_list,name=cd,if=cooldown.fists_of_fury.remains>1
actions.serenity_opener+=/serenity,if=cooldown.fists_of_fury.remains>1
actions.serenity_opener+=/rising_sun_kick,target_if=min:debuff.mark_of_the_crane.remains,if=active_enemies<3&buff.serenity.up
actions.serenity_opener+=/blackout_kick,target_if=min:debuff.mark_of_the_crane.remains,if=(!prev_gcd.1.blackout_kick)
actions.serenity_opener+=/fists_of_fury,if=cooldown.rising_sun_kick.remains>1,interrupt=1
# Cast Fists_of_fury if
# - Rising Sun Kicks remaining cooldown is longer than 1 second
# - Interrupt Fists_of_fury with Rising Sun Kick if Serenity remains
actions.serenity_opener+=/blackout_kick,target_if=min:debuff.mark_of_the_crane.remains,if=buff.serenity.down&chi<=2&cooldown.serenity.remains<=0&prev_gcd.1.tiger_palm
actions.serenity_opener+=/tiger_palm,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&chi=1
actions.serenity=tiger_palm,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy=energy.max&chi<1&!buff.serenity.up
actions.serenity+=/call_action_list,name=cd
actions.serenity+=/serenity
actions.serenity+=/rising_sun_kick,target_if=min:debuff.mark_of_the_crane.remains,if=active_enemies<3
actions.serenity+=/blackout_kick,target_if=min:debuff.mark_of_the_crane.remains,if=(!prev_gcd.1.blackout_kick)&(prev_gcd.1.fists_of_fury)&active_enemies<2
actions.serenity+=/fists_of_fury,if=((equipped.drinking_horn_cover&buff.pressure_point.remains<=2&set_bonus.tier20_4pc)&(cooldown.rising_sun_kick.remains>1|active_enemies>1)),interrupt=1
#Legacy syntax for T19/T20 6pc
actions.serenity+=/fists_of_fury,if=(|buff.bloodlust.up|buff.serenity.remains<1)&(cooldown.rising_sun_kick.remains>1|active_enemies>1)),interrupt=1
# Cast Fist of Fury if:
# - The remaining cooldown on rising_sun_kick is longer than the channel duration of Fists_of_fury
actions.serenity+=/spinning_crane_kick,if=active_enemies>=3&!prev_gcd.1.spinning_crane_kick
actions.serenity+=/rushing_jade_wind,if=!prev_gcd.1.rushing_jade_wind&buff.rushing_jade_wind.down&buff.serenity.remains>=4
# Needs to be rewritten for BFA
actions.serenity+=/rising_sun_kick,target_if=min:debuff.mark_of_the_crane.remains,if=active_enemies>=3
actions.serenity+=/rushing_jade_wind,if=!prev_gcd.1.rushing_jade_wind&buff.rushing_jade_wind.down&active_enemies>1
# Needs to be rewritten for BFA
actions.serenity+=/spinning_crane_kick,if=!prev_gcd.1.spinning_crane_kick
actions.serenity+=/blackout_kick,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick

# Actions.AoE is intended for use with Hectic_Add_Cleave and currently needs to be optimized
actions.aoe=call_action_list,name=cd
actions.aoe+=/energizing_elixir,if=!prev_gcd.1.tiger_palm&chi<=1&(cooldown.rising_sun_kick.remains=0|energy<50)
actions.aoe+=/arcane_torrent,if=chi.max-chi>=1&energy.time_to_max>=0.5
actions.aoe+=/fists_of_fury,if=talent.serenity.enabled&cooldown.serenity.remains>=5&energy.time_to_max>2
actions.aoe+=/fists_of_fury,if=!talent.serenity.enabled&energy.time_to_max>2
actions.aoe+=/fists_of_fury,if=cooldown.rising_sun_kick.remains>=3.5&chi<=5
actions.aoe+=/whirling_dragon_punch
actions.aoe+=/rising_sun_kick,target_if=cooldown.whirling_dragon_punch.remains>=gcd&!prev_gcd.1.rising_sun_kick&cooldown.fists_of_fury.remains>gcd
actions.aoe+=/rushing_jade_wind,if=chi.max-chi>1&!prev_gcd.1.rushing_jade_wind
# Needs to be rewritten for BFA
actions.aoe+=/chi_burst,if=chi<=2&(cooldown.rising_sun_kick.remains>=5|cooldown.whirling_dragon_punch.remains>=5)&energy.time_to_max>1
actions.aoe+=/spinning_crane_kick,if=active_enemies>=3&!prev_gcd.1.spinning_crane_kick
actions.aoe+=/blackout_kick,target_if=min:debuff.mark_of_the_crane.remains,if=(chi>1|buff.bok_proc.up|(talent.energizing_elixir.enabled&cooldown.energizing_elixir.remains<cooldown.fists_of_fury.remains))&((cooldown.rising_sun_kick.remains>1&chi>4)&(cooldown.fists_of_fury.remains>1|chi>2)|prev_gcd.1.tiger_palm)&!prev_gcd.1.blackout_kick
actions.aoe+=/tiger_palm,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&(chi.max-chi>=2|energy.time_to_max<3)
actions.aoe+=/tiger_palm,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy.time_to_max<=1&chi.max-chi>=2
actions.aoe+=/chi_wave,if=chi<=3&(cooldown.rising_sun_kick.remains>=5|cooldown.whirling_dragon_punch.remains>=5)&energy.time_to_max>1
actions.aoe+=/chi_wave

# default action list
actions.st=invoke_xuen_the_white_tiger
actions.st+=/storm_earth_and_fire,if=!buff.storm_earth_and_fire.up
actions.st+=/energizing_elixir,if=!prev_gcd.1.tiger_palm

# T21 set bonus conditional
# Cast Blackout Kick if:
# - Previous GCD was not Blackout Kick
# - Blackout Kick! is available
# - You're not at max Chi
actions.st+=/blackout_kick,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&chi.max-chi>=1&set_bonus.tier21_4pc&buff.bok_proc.up

# Cast Tiger Palm if:
# - Previous GCD was not Tiger Palm
# - Previous GCD was not EE (NOTE: redundant because of the Energy check, needs to be rewritten for BFA)
# - You will cap Energy before next GCD
# - You will gain 2 or more Chi
actions.st+=/tiger_palm,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&energy.time_to_max<=1&chi.max-chi>=2
# Cast FotWT if you will gain 3 or more Chi
actions.st+=/fist_of_the_white_tiger,if=chi.max-chi>=3
actions.st+=/whirling_dragon_punch

# Cast Rising Sun Kick if:
# - You are using SEF, and you have 3 or more Chi AND 40 or more energy OR 5 or more Chi
# - You are using Serenity, 6 or more seconds remain on the cooldown of Serenity, and you have 3 or more Chi AND 40 or more energy OR 5 or more Chi 
actions.st+=/rising_sun_kick,target_if=min:debuff.mark_of_the_crane.remains,if=((chi>=3&energy>=40)|chi>=5)&(!talent.serenity.enabled|cooldown.serenity.remains>=6)
#Legacy conditional for drinking_horn_cover
actions.st+=/fists_of_fury,if=talent.serenity.enabled&!equipped.drinking_horn_cover&cooldown.serenity.remains>=5&energy.time_to_max>2
#Legacy conditional for drinking_horn_cover
actions.st+=/fists_of_fury,if=talent.serenity.enabled&equipped.drinking_horn_cover&(cooldown.serenity.remains>=15|cooldown.serenity.remains<=4)&energy.time_to_max>2
# Cast Fists of Fury if:
# - You are using SEF
actions.st+=/fists_of_fury,if=!talent.serenity.enabled
# Cast Fists of Fury if:
# - Rising Sun Kick will not come off cooldown during the channel
actions.st+=/fists_of_fury,if=cooldown.fists_of_fury.duration<=cooldown.rising_sun_kick.remains
# Cast RSK if:
# - You are using SEF OR you are using Serenity and 5 or more seconds remain on the cooldown of Serenity
actions.st+=/rising_sun_kick,target_if=min:debuff.mark_of_the_crane.remains,if=(!talent.serenity.enabled|cooldown.serenity.remains>=5)
# Cast Blackout Kick if:
# - Previous GCD was not BoK
# - You are not at max Chi
actions.st+=/blackout_kick,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.blackout_kick&chi.max-chi>=1
#Legacy for the_emperors_capacitor
actions.st+=/crackling_jade_lightning,if=equipped.the_emperors_capacitor&buff.the_emperors_capacitor.stack>=19&energy.time_to_max>3
actions.st+=/crackling_jade_lightning,if=equipped.the_emperors_capacitor&buff.the_emperors_capacitor.stack>=14&cooldown.serenity.remains<13&talent.serenity.enabled&energy.time_to_max>3
# Cast spinning_crane_kick if:
# - Previous cast was not spinning_crane_kick
# - You have 3 or more active enemies (NOTE: Does not include stacks. May be redundant since actions.st should not be called given the earlier check)
actions.st+=/spinning_crane_kick,if=active_enemies>=3&!prev_gcd.1.spinning_crane_kick
actions.st+=/blackout_kick

# Will need to be rewritten for BFA
# Current rule: Cast Chi Burst if:
# - You have 3 or less Chi
# - RSK is up in 5 or more seconds OR WDP is up in 5 or more seconds
# - You will not cap energy before the next GCD
actions.st+=/chi_burst,if=chi<=3&(cooldown.rising_sun_kick.remains>=5|cooldown.whirling_dragon_punch.remains>=5)&energy.time_to_max>1

# Cast Tiger Palm if:
# - Previous ability was not Tiger Palm or Energizing Elixir
# - You will gain at least 2 Chi, OR you will cap energy within 3 seconds (NOTE: Could cast TP even at 5 Chi just to prevent energy capping, in theory)
actions.st+=/tiger_palm,target_if=min:debuff.mark_of_the_crane.remains,if=!prev_gcd.1.tiger_palm&!prev_gcd.1.energizing_elixir&(chi.max-chi>=2|energy.time_to_max<3)

actions.st+=/chi_wave
actions.st+=/chi_burst
#actions.st+=/flying_serpent_kick
#actions.st+=/rushing_jade_wind
