/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef TITANIC_SOUND_H
#define TITANIC_SOUND_H

#include "titanic/support/simple_file.h"
#include "titanic/sound/proximity.h"
#include "titanic/sound/sound_manager.h"
#include "titanic/sound/sound_resource.h"
#include "titanic/core/list.h"
#include "titanic/core/view_item.h"
#include "titanic/true_talk/dialogue_file.h"

namespace Titanic {

class CGameManager;

class CSoundItem : public ListItem {
public:
	CString _name;
	CSoundResource *_soundResource;
	File *_dialogueFileHandle;
	int _speechId;
	int _field24;
	int _field28;
public:
	CSoundItem() : ListItem(), _soundResource(nullptr), _dialogueFileHandle(nullptr),
		_speechId(0), _field24(0), _field28(0) {}
	CSoundItem(const CString &name) : ListItem(), _name(name), _soundResource(nullptr),
		_dialogueFileHandle(nullptr), _speechId(0), _field24(0), _field28(0) {}
	CSoundItem(File *dialogueFile, int speechId) : ListItem(), _soundResource(nullptr),
		_dialogueFileHandle(dialogueFile), _speechId(speechId), _field24(0), _field28(0) {}

	int fn1();
};

class CSoundItemList : public List<CSoundItem> {
};

class CSound {
private:
	CGameManager *_gameManager;
	CSoundItemList _sounds;
private:
	/**
	 * Check whether any sounds are done and can be be removed
	 */
	void checkSounds();

	/**
	 * Removes the oldest sound from the sounds list that isn't
	 * currently playing
	 */
	void removeOldest();
public:
	QSoundManager _soundManager;
public:
	CSound(CGameManager *owner);

	/**
	 * Save the data for the class to file
	 */
	void save(SimpleFile *file) const;

	/**
	 * Load the data for the class from file
	 */
	void load(SimpleFile *file);

	/**
	 * Called when a game is about to be loaded
	 */
	void preLoad();

	/**
	 * Called when loading a game is complete
	 */
	void postLoad() { _soundManager.postLoad(); }

	/**
	 * Called when a game is about to be saved
	 */
	void preSave() { _soundManager.preSave(); }

	/**
	 * Called when a game has finished being saved
	 */
	void postSave() { _soundManager.postSave(); }

	/**
	 * Called when the view has been changed
	 */
	void preEnterView(CViewItem *newView, bool isNewRoom);

	bool fn1(int val);
	void fn2(int handle);
	void fn3(int handle, int val2, int val3);
	void fn4(CSoundResource *soundRes, int val);
		
	void managerProc8(int v) { _soundManager.proc8(v); }

	CSoundItem *getTrueTalkSound(CDialogueFile *dialogueFile, int index);

	/**
	 * Load a sound
	 * @param name		Name of sound resource
	 * @returns			Sound item record
	 */
	CSoundResource *loadSpeech(CDialogueFile *dialogueFile, int speechId);

	/**
	 * Play a speech
	 */
	int playSpeech(CDialogueFile *dialogueFile, int speechId, CProximity &prox);

	/**
	 * Load a sound
	 * @param name		Name of sound resource
	 * @returns			Sound item record
	 */
	CSoundResource *loadSound(const CString &name);

	/**
	 * Play a sound
	 */
	int playSound(const CString &name, CProximity &prox);
};

} // End of namespace Titanic

#endif /* TITANIC_SOUND_H */