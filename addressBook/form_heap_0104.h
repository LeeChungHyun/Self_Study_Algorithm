//form.h
#ifndef _FORM_H
#define _FORM_H
typedef struct _addressBook AddressBook;

void DisplayMenu();
void FormForRecording(AddressBook* addressBook);
void FormForFinding(AddressBook* addressBook);
void FormForCorrecting(AddressBook* addressBook);
void FormForErasing(AddressBook* addressBook);
void FormForArranging(AddressBook* addressBook);
void FormForShowAll(AddressBook* addressBook);
#endif // !_FORM_H
