/* * Dana - Dana, Symbol of Wisdom
 * Copyright (C) 2014 Mostafa Sedaghat Joo (mostafa.sedaghat@gmail.com)
 *
 * This file is part of Dana.
 *
 * Dana is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dana is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dana.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STRINGS_H
#define __STRINGS_H




/// info
#define INFO_MSG_DECK_MERGE_STATE                        QString("%1 card(s) added successfully.")

/// warning
#define WNG_CARD_CHANGED_TITLE                           QString("Save card")
#define WNG_CARD_CHANGED                                 QString("The card has changed. Do you want to save it?")
#define WNG_REMOVE_DECK_TITLE                            QString("Remove deck")
#define WNG_REMOVE_DECK                                  QString("Are you sure you want to delete '%1'?\nYou will lose all the flash cards inside the deck.")
#define WNG_REMOVE_CARD_TITLE                            QString("Remove card")
#define WNG_REMOVE_CARD                                  QString("Are you sure you want to delete '%1'?")
#define WNG_ASKING_FOR_UPDATE_REMOTE_DECK_TITLE          QString("Updating deck")
#define WNG_ASKING_FOR_UPDATE_REMOTE_DECK                QString("You have uploaded this deck before. Do you want to update it?")
#define WNG_ASKING_FOR_MERGE_TITLE                       QString("Merging deck")
#define WNG_ASKING_FOR_MERGE                             QString("This deck exeist in your local desk. Do you want to merge it for any posible changes?")

/// error
#define ERR_QT_SPEECH_FAILED                             QString("An error occurred during using your TTS system.\nPlease check it and ensure it installed properly.")
#define ERR_MSG_DECK_EXPORT_FAILD                        QString("An error occurred during exporting deck.\nTry again and if error still persists please report it.")
#define ERR_MSG_DECK_IMPORT_FAILD                        QString("An error occurred during importing deck.\nTry again and if error still persists please report it.")
#define ERR_LOAD_DECK_FAILED                             QString("An error occurred during loading deck.\nTry again and if error still persists please report it.")
#define ERR_UNAUTHORIZED_TO_UPLOAD                       QString("A deck with this guid already exists. You are not authorized to change it.")


/// general
#define STR_NOPE                                         QString("")
#define STR_MENU_DECK                                    QString("&Deck")
#define STR_MENU_CARD                                    QString("&Card")
#define STR_MENU_ACTION                                  QString("&Action")
#define STR_MENU_HELP                                    QString("&Help")
#define STR_MENU_CARD_SET_LEVEL                          QString("Set &level")
#define STR_CARD                                         QString("Card")
#define STR_DECK                                         QString("Deck")
#define STR_CARDS                                        QString("Cards")
#define STR_DECKS                                        QString("Decks")
#define STR_ALL_LEVELS                                   QString("All levels")
#define STR_LEVEL_1                                      QString("Level 1")
#define STR_LEVEL_2                                      QString("Level 2")
#define STR_LEVEL_3                                      QString("Level 3")
#define STR_LEVEL_4                                      QString("Level 4")
#define STR_LEVEL_5                                      QString("Level 5")
#define STR_STARREDS                                     QString("Starreds")
#define STR_RETIREES                                     QString("Retirees")
#define STR_ALL_CARDS                                    QString("All cards")
#define STR_LEVEL_COUNT                                  QString("Total")
#define STR_CARD_NUMBER_EMPTY                            QString("Empty")
#define STR_CARD_NUMBER_ONE                              QString("1 card")
#define STR_CARD_NUMBER_MORE                             QString("%1 cards")
#define STR_DECK_DOWNLOADS                               QString("%1 downloads")
#define STR_DECK_DOWNLOADS_1                             QString("Downloads")
#define STR_EXIT_DIALOG                                  QString("&Exit")
#define STR_EXIT_DIALOG_TIP                              QString("Exit dialog. Discard changes, if any")
#define STR_STARRED                                      QString("Starred")
#define STR_MERGE                                        QString("Merge")
#define STR_CONNECT                                      QString("Connect")
#define STR_NETWORK_ERROR                                QString("Network error")
#define STR_CANCEL_PROGRESS                              QString("&Cancel")
#define STR_ERROR                                        QString("Error")
#define STR_QUESTION                                     QString("")
#define STR_WARNING                                      QString("Warning")
#define STR_INFORMATION                                  QString("")
#define STR_UPDATE_DANA                                  QString("Update Dana")

/// status bar
#define STR_STATUS_READY                                 QString("Ready")


/// actions
#define STR_ACTION_RESTORE                               QString("&Restore")
#define STR_ACTION_QUIT                                  QString("E&xit")
#define STR_ACTION_ABOUT                                 QString("&About Dana")
#define STR_ACTION_SUPPORT                               QString("&Support Dana")
#define STR_ACTION_UPDATE_CHECK                          QString("Check for &upadate")
#define STR_ACTION_REPORT_BUG                            QString("Report a &bug")
#define STR_ACTION_DOWNLOAD                              QString("&Download")
#define STR_ACTION_CONFIG                                QString("&Preferences")
#define STR_ACTION_SHOW_QUERY                            QString("Show &quick query")
#define STR_ACTION_CARD_NEW                              QString("&New card")
#define STR_ACTION_CARD_OPEN                             QString("&Open card")
#define STR_ACTION_CARD_REMOVE                           QString("&Remove card")
#define STR_ACTION_CARD_STAR                             QString("S&tar/Unstar card")
#define STR_ACTION_CARD_INFO                             QString("Card &info")
#define STR_ACTION_DECK_SAVE                             QString("&Save deck")
#define STR_ACTION_DECK_QUERY                            QString("Start &duery")
#define STR_ACTION_DECK_QUICK_QUERY                      QString("Start q&uick query")
#define STR_ACTION_DECK_STUDY                            QString("&Study")
#define STR_ACTION_DECK_REVIEW                           QString("Revie&w")
#define STR_ACTION_DECK_REPORT                           QString("Re&port chart")
#define STR_ACTION_DECK_OPEN                             QString("&Open deck")
#define STR_ACTION_DECK_CREATE                           QString("&Create deck")
#define STR_ACTION_DECK_MERGE                            QString("&Merge deck")
#define STR_ACTION_DECK_IMPORT                           QString("&Import deck")
#define STR_ACTION_DECK_EXPORT                           QString("&Export deck")
#define STR_ACTION_DECK_DOWNLOAD                         QString("&Download deck")
#define STR_ACTION_DECK_UPLOAD                           QString("Upload and &share deck")
#define STR_ACTION_DECK_EDIT                             QString("&Edit deck")
#define STR_ACTION_DECK_REMOVE                           QString("&Remove deck")
#define STR_ACTION_DECK_PROPERTIES                       QString("&Properties")
#define STR_ACTION_BACK_TO_DESK                          QString("Back to &desk")

#define STR_ACTION_RESTORE_TIP                           QString("Restore main window")
#define STR_ACTION_QUIT_TIP                              QString("Exit Dana")
#define STR_ACTION_ABOUT_TIP                             QString("About Dana")
#define STR_ACTION_SUPPORT_TIP                           QString("Support Dana")
#define STR_ACTION_UPDATE_CHECK_TIP                      QString("Check for upadate")
#define STR_ACTION_REPORT_BUG_TIP                        QString("Report a bug")
#define STR_ACTION_DOWNLOAD_TIP                          QString("Download")
#define STR_ACTION_CONFIG_TIP                            QString("Show preferences dialog")
#define STR_ACTION_CARD_NEW_TIP                          QString("Insert a new flash card to the deck")
#define STR_ACTION_CARD_OPEN_TIP                         QString("Open/Edit selected flash card")
#define STR_ACTION_CARD_REMOVE_TIP                       QString("Delete selected flash card from the deck")
#define STR_ACTION_CARD_STAR_TIP                         QString("Star a unstarred card -or- unstar a starred card(starred cards will be shown at the top of the table)")
#define STR_ACTION_CARD_INFO_TIP                         QString("Show the card history")
#define STR_ACTION_DECK_SAVE_TIP                         QString("Save all changes")
#define STR_ACTION_DECK_QUERY_TIP                        QString("Start a query")
#define STR_ACTION_DECK_QUICK_QUERY_TIP                  QString("Start a query")
#define STR_ACTION_DECK_STUDY_TIP                        QString("&Study")
#define STR_ACTION_DECK_REVIEW_TIP                       QString("Review all the cards")
#define STR_ACTION_DECK_REPORT_TIP                       QString("Report chart")
#define STR_ACTION_DECK_OPEN_TIP                         QString("Open selected deck")
#define STR_ACTION_DECK_CREATE_TIP                       QString("Add a new deck")
#define STR_ACTION_DECK_MERGE_TIP                        QString("Merge this deck with new one")
#define STR_ACTION_DECK_IMPORT_TIP                       QString("Import a deck from file")
#define STR_ACTION_DECK_EXPORT_TIP                       QString("Export selected deck to a file")
#define STR_ACTION_DECK_DOWNLOAD_TIP                     QString("Download a deck from server")
#define STR_ACTION_DECK_UPLOAD_TIP                       QString("Upload selected deck to server")
#define STR_ACTION_DECK_EDIT_TIP                         QString("Edit selected deck")
#define STR_ACTION_DECK_REMOVE_TIP                       QString("Remove selected deck")
#define STR_ACTION_DECK_PROPERTIES_TIP                   QString("Check deck properties")
#define STR_ACTION_BACK_TO_DESK_TIP                      QString("Back to &desk")

/// deck
#define STR_DECK_NEW                                     QString("New deck")
#define STR_DECK_SAVE                                    QString("&Save")
#define STR_DECK_SAVE_TIP                                QString("Save this deck")
#define STR_DECK_NAME                                    QString("Name")
#define STR_DECK_AUTHOR                                  QString("Author")
#define STR_DECK_GUID                                    QString("UID")
#define STR_DECK_TAGS                                    QString("Tags")
#define STR_DECK_CREATED_TIME                            QString("Created time")
#define STR_DECK_UPDATED_TIME                            QString("Last modification")
#define STR_DECK_CARD_FORMAT                             QString("Card format")
#define STR_DECK_DESC                                    QString("Description")
#define STR_DECK_TOTAL_CARD_NO                           QString("Total card number")
#define STR_DECK_CARD_NO                                 QString("Card number")


/// deck dialog
#define STR_DECK_CHANGE_FORMAT_LINK                      QString("<a href='#'>Change format</a>")
#define STR_DECK_TAGS_HELP                               QString("Separate tags with comma, like: dana, french, essential words")
#define STR_DECK_FRONT_POLICY_LABEL                      QString("Front editor policy")
#define STR_DECK_BACK_POLICY_LABEL                       QString("Back editor policy")

/// card
#define STR_CARD_FRONT_SIDE                              QString("Front side")
#define STR_CARD_BACK_SIDE                               QString("Back side")
#define STR_CARD_REVIEW_TIP                              QString("Review this card")
#define STR_CARD_DIFFICULTY_HARD                         QString("Hard")
#define STR_CARD_DIFFICULTY_NORMAL                       QString("Normal")
#define STR_CARD_DIFFICULTY_EASY                         QString("Easy")

/// card dialog
#define STR_CARD_DIALOG_KEEP_OPEN                        QString("Do&n't close this dialog after saving")

/// query
#define STR_QUERY_QUESTION                               QString("How do you feel? It's ...")
#define STR_QUERY_FRONT_2_BACK                           QString("Front to back")
#define STR_QUERY_BACK_2_FRONT                           QString("Back to front")
#define STR_QUERY_STOP_QUERY_TIP                         QString("Stop ")
#define STR_QUERY_HISTOGRAPH_TIP                         QString("Histograph")

/// card dialog window
#define STR_CARD_EASY                                    QString("&Easy")
#define STR_CARD_EASY_TIP                                QString("Easy, increase level")
#define STR_CARD_HARD                                    QString("&Hard")
#define STR_CARD_HARD_TIP                                QString("Hard, decrease level")
#define STR_CARD_NEW                                     QString("New card")
#define STR_CARD_NEW_TIP                                 QString("Add new card")
#define STR_CARD_SAVE                                    QString("&Save")
#define STR_CARD_SAVE_TIP                                QString("Save this card (Ctrl+S)")
#define STR_CARD_NEXT                                    QString("&Next card")
#define STR_CARD_NEXT_TIP                                QString("Goto next card in deck")
#define STR_CARD_PREV                                    QString("&Previous card")
#define STR_CARD_PREV_TIP                                QString("Goto previous card in deck")
#define STR_CARD_LISTEN                                  QString("Listen to the card")
#define STR_CARD_LISTEN_TIP                              QString("Listen to the card (Ctrl+D)")
#define STR_CARD_FORMAT_SAMPLE_TEXT                      QString("sample_text")
#define STR_CARD_HISTORY                                 QString("Card history")
#define STR_CARD_HISTORY_TIME                            QString("Time")
#define STR_CARD_HISTORY_LEVEL                           QString("Level")

/// download dialog
#define STR_DOWNLOAD_DIALOG_SORT_BY_DATE                 QString("Sort by date")
#define STR_DOWNLOAD_DIALOG_SORT_BY_NAME                 QString("Sort by name")
#define STR_DOWNLOAD_DIALOG_SORT_BY_CARD_NUMBER          QString("Sort by card number")
#define STR_DOWNLOAD_DIALOG_SORT_BY_DOWNLOADS            QString("Sort by downloads")
#define STR_DOWNLOAD_DIALOG_SORT_BY_RATING               QString("Sort by rating")
#define STR_DOWNLOAD_DIALOG_VIEW_OPTION_LIST             QString("List view")
#define STR_DOWNLOAD_DIALOG_VIEW_OPTION_DETAIL           QString("Detail view")

/// progress dialog
#define STR_PROGRESS_DIALOG_UPLOAD_CAPTION               QString("Uploading ...")
#define STR_PROGRESS_DIALOG_DOWNLOAD_CAPTION             QString("Downloading ...")

/// preferences
#define STR_CONFIG_AUTO_START_CAPTION                    QString("Start dana automatically when you start your computer")
#define STR_CONFIG_AUTO_UPDATE_CHECK                     QString("Automatic check for update")
#define STR_CONFIG_CAPTION_GENERAL                       QString("General settings")
#define STR_CONFIG_CAPTION_DECK                          QString("Deck settings")
#define STR_CONFIG_CAPTION_NETWORK                       QString("Netword settings")
#define STR_CONFIG_LIST_GENERAL                          QString("General")
#define STR_CONFIG_LIST_DECK                             QString("Deck")
#define STR_CONFIG_LIST_NETWORK                          QString("Network")
#define STR_CONFIG_DECK_TIMER_LABEL                      QString("Show quick query dialog each")
#define STR_CONFIG_DECK_QUERY_TIMER_FORMAT               QString("%1 minutes")
#define STR_CONFIG_DECK_POLICY_ACCEPT_RICH               QString("Accept rich text")
#define STR_CONFIG_DECK_POLICY_ACCEPT_PLAIN              QString("Accept plain text")
#define STR_CONFIG_NETWORD_LOGGED_OUT_LABEL              QString("you have not logged in.")
#define STR_CONFIG_NETWORD_LOGGED_IN_LABEL               QString("you have logged in as <b>%1</b>")

/// dialogs
#define STR_DIALOG_TITLE_ABOUT                           QString("About")
#define STR_DIALOG_TITLE_ADD_CARD                        QString("Add card")
#define STR_DIALOG_TITLE_EDIT_CARD                       QString("Edit card")
#define STR_DIALOG_TITLE_QUERY                           QString("Query")
#define STR_DIALOG_TITLE_STUDY                           QString("Study")
#define STR_DIALOG_TITLE_FORMAT                          QString("Format card")
#define STR_DIALOG_TITLE_CONFIG                          QString("Preferences")
#define STR_DIALOG_TITLE_EDIT_DECK                       QString("Edit deck")
#define STR_DIALOG_TITLE_ADD_DECK                        QString("Add deck")
#define STR_DIALOG_TITLE_VIEW_DECK                       QString("Deck")
#define STR_DIALOG_TITLE_DOWNLOAD                        QString("Download deck")
#define STR_DIALOG_TITLE_LOGIN                           QString("Login")
#define STR_DIALOG_TITLE_MERGE                           QString("Merge decks")
#define STR_DIALOG_TITLE_PROXY                           QString("Proxy")
#define STR_DIALOG_TITLE_PROGRESS                        QString("Progress")
#define STR_DIALOG_TITLE_REVIEW                          QString("Review")
#define STR_DIALOG_TITLE_REPORT                          QString("Report")
#define STR_DIALOG_TITLE_CARD_INFO                       QString("Card info")

/// about dialog

/// card dialog

/// merge dialog
#define STR_MERGE_GROUP_CONFLICT                         QString("In case of conflicting")
#define STR_MERGE_SOURCE_DECK_LABLE                      QString("You want to merge (Source):")
#define STR_MERGE_DEST_DECK_LABLE                        QString("With (destination):")
#define STR_MERGE_CONFLICT_OPTION_SOURCE                 QString("Accept &Source")
#define STR_MERGE_CONFLICT_OPTION_DEST                   QString("Accept &destination")
#define STR_MERGE_CONFLICT_OPTION_AUTO                   QString("Auto &merge")

/// proxy dialog
#define STR_PROXY_REQUEST                                QString("Proxy authentication is required.")
#define STR_PROXY_GROUP_PROXY                            QString("Proxy")
#define STR_PROXY_USERNAME                               QString("Username")
#define STR_PROXY_PASSWORD                               QString("Password")
#define STR_PROXY_HOST                                   QString("Host")
#define STR_PROXY_PORT                                   QString("Port")

/// login dialog
#define STR_LOGIN_LOGIN                                  QString("Login")
#define STR_LOGIN_LOGOUT                                 QString("Logout")
#define STR_LOGIN_GROUP_ACCOUNT                          QString("Account information")
#define STR_LOGIN_EMAIL                                  QString("Email")
#define STR_LOGIN_PASSWORD                               QString("Password")
#define STR_LOGIN_REMEMBER_ME                            QString("Remember me on this computer")
#define STR_LOGIN_CREATE_ACCOUNT                         QString("<a href='http://dana-box.com/dana/register.php'>Create a free account</a>")
#define STR_LOGIN_CREATE_FORGET_PASSWORD                 QString("<a href='http://dana-box.com/dana/forgot_password.php?email=%1'>Forgotten your password?")

/// report dialog
#define STR_REPORT_HEADER_LEVEL                          QString("Level")
#define STR_REPORT_HEADER_COUNT                          QString("Count")

#define ICON_ABOUT                                       QIcon(":/images/about.png")
#define ICON_DESK                                        QIcon(":/images/desk.png")
#define ICON_CARD                                        QIcon(":/images/card.png")
#define ICON_DECK                                        QIcon(":/images/deck.png")
#define ICON_CARD_NEW                                    QIcon(":/images/card-new.png")
#define ICON_CARD_OPEN                                   QIcon(":/images/card-open.png")
#define ICON_CARD_REMOVE                                 QIcon(":/images/card-remove.png")
#define ICON_CARD_INFO                                   QIcon(":/images/card-info.png")
#define ICON_DECK_OPEN                                   QIcon(":/images/deck-open.png")
#define ICON_DECK_CREATE                                 QIcon(":/images/deck-create.png")
#define ICON_DECK_MERGE                                  QIcon(":/images/deck-merge.png")
#define ICON_DECK_IMPORT                                 QIcon(":/images/deck-import.png")
#define ICON_DECK_EXPORT                                 QIcon(":/images/deck-export.png")
#define ICON_DECK_DOWNLOAD                               QIcon(":/images/deck-download.png")
#define ICON_DECK_UPLOAD                                 QIcon(":/images/deck-upload.png")
#define ICON_DECK_EDIT                                   QIcon(":/images/deck-edit.png")
#define ICON_DECK_REMOVE                                 QIcon(":/images/deck-remove.png")
#define ICON_DECK_SAVE                                   QIcon(":/images/save.png")
#define ICON_DECK_QUERY                                  QIcon(":/images/query.png")
#define ICON_DECK_QUICK_QUERY                            QIcon(":/images/quick-query.png")
#define ICON_DECK_STUDY                                  QIcon(":/images/study.png")
#define ICON_DECK_REVIEW                                 QIcon(":/images/review.png")
#define ICON_DECK_REPORT                                 QIcon(":/images/pie.png")
#define ICON_STARRED                                     QIcon(":/images/Starred.png")
#define ICON_STOP                                        QIcon(":/images/pause.png")
#define ICON_FILTER                                      QIcon(":/images/filter.png")
#define ICON_SORT                                        QIcon(":/images/sort.png")
#define ICON_VIEW_OPTIONS                                QIcon(":/images/view-options.png")
#define ICON_FLIP                                        QIcon(":/images/flip.png")
#define ICON_EXIT                                        QIcon(":/images/exit.png")
#define ICON_SAVE                                        QIcon(":/images/save.png")
#define ICON_LISTEN                                      QIcon(":/images/listen.png")
#define ICON_THUMB_UP                                    QIcon(":/images/thumb-up.png")
#define ICON_THUMB_DOWN                                  QIcon(":/images/thumb-down.png")
#define ICON_NEXT                                        QIcon(":/images/next.png")
#define ICON_PREV                                        QIcon(":/images/prev.png")
#define ICON_ABOUT                                       QIcon(":/images/about.png")
#define ICON_CONFIG                                      QIcon(":/images/config.png")
#define ICON_CONFIG_GENERAL                              QIcon(":/images/config-general.png")
#define ICON_CONFIG_DECK                                 QIcon(":/images/config-deck.png")
#define ICON_CONFIG_NETWORK                              QIcon(":/images/config-network.png")

#define PIXMAP_DANA_TRAY                                 QPixmap(":/images/dana_tray.png")
#define PIXMAP_DANA_16                                   QPixmap(":/images/dana_16.png")
#define PIXMAP_DANA_24                                   QPixmap(":/images/dana_24.png")
#define PIXMAP_DANA_32                                   QPixmap(":/images/dana_32.png")
#define PIXMAP_DANA_48                                   QPixmap(":/images/dana_48.png")
#define PIXMAP_DANA_64                                   QPixmap(":/images/dana_64.png")
#define PIXMAP_DANA_72                                   QPixmap(":/images/dana_72.png")
#define PIXMAP_DANA_96                                   QPixmap(":/images/dana_96.png")
#define PIXMAP_DECK_24                                   QPixmap(":/images/deck_24.png")
#define PIXMAP_DECK_48                                   QPixmap(":/images/deck_48.png")
#define PIXMAP_DECK_64                                   QPixmap(":/images/deck_64.png")
#define PIXMAP_DECK_96                                   QPixmap(":/images/deck_96.png")
#define PIXMAP_DIFFICULTY_HARD                           QPixmap(":/images/difficulty-hard.png")
#define PIXMAP_DIFFICULTY_NORMAL                         QPixmap(":/images/difficulty-normal.png")
#define PIXMAP_DIFFICULTY_EASY                           QPixmap(":/images/difficulty-easy.png")
#define PIXMAP_RETIREE                                   QPixmap(":/images/completed.png")
#define PIXMAP_STARRED                                   QPixmap(":/images/starred.png")
#define PIXMAP_UNSTARRED                                 QPixmap(":/images/unstarred.png")
#define PIXMAP_CLOSE                                     QPixmap(":/images/close.png")
#define PIXMAP_SEARCH                                    QPixmap(":/images/search.png")

#endif // __STRINGS_H
