from django import forms
from .models import CustomUser
from django.core.exceptions import ValidationError


class UpdateUsernameForm(forms.Form):
    new_username = forms.CharField(max_length=150, required=True)

    def clean_new_username(self):
        new_username = self.cleaned_data["new_username"]
        # Verifica se il nuovo username è già in uso
        if CustomUser.objects.filter(username=new_username).exists():
            raise ValidationError(
                "This username is already in use. Please choose a different one."
            )
        return new_username


class UpdateProfileImageForm(forms.ModelForm):

    profile_image = forms.ImageField(required=False)  # Aggiunto il campo del file

    class Meta:
        model = CustomUser
        fields = ["profile_image"]
